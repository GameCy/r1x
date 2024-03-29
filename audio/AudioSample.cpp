#include "AudioSample.h"
#include <qmath.h>
#include <qendian.h>
#include <QDebug>
#include <QMediaDevices>

AudioSample::AudioSample(QObject *parent, WavBuffer *wavBuffer)
    : QIODevice(parent)
    , buffer(wavBuffer)
    , audioSink(nullptr)
    , device(QMediaDevices::defaultAudioOutput())
    , bytePosition(0)
    , looping(false)
    , volume(0.8)
    , slideVolumeTimerId(0)
{
    extractFormatFromWav( format, buffer );
    if (!device.isFormatSupported(format))
    {
        qWarning() << "Default format not supported - trying to use nearest";
        format = device.preferredFormat();
    }
    open(ReadOnly);
    audioSink = new QAudioSink(format, nullptr);
    connect(audioSink, &QAudioSink::stateChanged, this, &AudioSample::AudioStateChanged);
}

AudioSample::~AudioSample()
{
    if (slideVolumeTimerId!=0)
        killTimer(slideVolumeTimerId);
    if (audioSink)
    {
        audioSink->stop();
        audioSink->disconnect(this);
        delete audioSink;//->deleteLater();
    }
    if (this->isOpen())
        close();
}

bool AudioSample::isPlaying()
{
    auto st = audioSink->state();
    return (st==QAudio::ActiveState || st==QAudio::IdleState); }

bool AudioSample::isStoped()             { return (audioSink->state()==QAudio::StoppedState); }

void AudioSample::Loop(bool value)       { looping = value; }

bool AudioSample::isLooping() const      { return looping; }


void AudioSample::Start()
{
    if (!isOpen())
        return;
    auto sinkState = audioSink->state();
    if (sinkState==QAudio::ActiveState || sinkState==QAudio::IdleState)
    {
        qWarning() << "audioSink is already in use";
        return;
    }

    bytePosition=0;
    audioSink->start(this);
    audioSink->setVolume(0.02f);
    slideVolumeTimerId = startTimer(1);
}

void AudioSample::Stop()
{
    audioSink->stop();
}

qint64 AudioSample::readData(char *data, qint64 maxlen)
{
    if (buffer->size()==0)
        return 0;

    qint64 requiredBytes = qMin(maxlen, (buffer->size() - bytePosition) );
    if (looping)
        requiredBytes = maxlen;

    qint64 bufferedBytes = 0;
    while(bufferedBytes<requiredBytes)
    {
        if (bytePosition>=buffer->size() )
            bytePosition = 0;
        qint64 chunk = qMin(maxlen, (buffer->size() - bytePosition) );
        memcpy(data, buffer->data().constData() + bytePosition, chunk);
        bytePosition += chunk;
        bufferedBytes += chunk;

        //qDebug() << "  --- chunk=" << chunk << " maxlen: " << maxlen
        //         << " bytePos: " << bytePosition << " required: " << requiredBytes;
    }

    return bufferedBytes;
}

qint64 AudioSample::writeData(const char *data, qint64 len)
{
    Q_UNUSED(data);
    Q_UNUSED(len);

    return 0;
}

qint64 AudioSample::bytesAvailable() const
{
    return buffer->size() + QIODevice::bytesAvailable();
}

void AudioSample::SetVolume(qreal vol)
{
    volume = vol;
    if (slideVolumeTimerId==0)
        slideVolumeTimerId = startTimer(1);
}

qreal AudioSample::GetVolume()
{
    return audioSink->volume();
}

QString AudioSample::path()
{
    return buffer? buffer->filePath() : "";
}

QAudioDevice &AudioSample::getDevice()
{
    return device;
}

void AudioSample::setDevice(const QAudioDevice &value)
{
    device = value;
}

void AudioSample::extractFormatFromWav(QAudioFormat &format, WavBuffer *wav)
{
    format.setSampleRate( wav->sampleRate() );
    format.setChannelCount( wav->channelsCount() );
    format.setSampleFormat( bitsToAudioFormat(wav->bitDepth()) );
    //format.setCodec("audio/pcm");
    //format.setByteOrder(QAudioFormat::LittleEndian);
    //format.setSampleType(QAudioFormat::SignedInt);
}

QAudioFormat::SampleFormat AudioSample::bitsToAudioFormat(int bits)
{
    if (bits == 8) return QAudioFormat::UInt8;
    if (bits ==16) return QAudioFormat::Int16;
    if (bits ==32) return QAudioFormat::Int32;
    //QAudioFormat::Float
    return QAudioFormat::Unknown;
}

void AudioSample::AudioStateChanged(QAudio::State newState)
{
//    qDebug() << "audio state " << newState << " sink error: " << audioSink->error()
//             << " bytePos: " << bytePosition << " bufferSize: " << buffer->size();

    if (newState==QAudio::IdleState &&
        bytePosition>=buffer->size() && !looping)
        audioSink->stop();
    if(newState==QAudio::StoppedState)
    {
        audioSink->reset();
        audioSink->disconnect();
        audioSink->deleteLater();

        audioSink = new QAudioSink(format, this);
        connect(audioSink, &QAudioSink::stateChanged, this, &AudioSample::AudioStateChanged);
    }
}

void AudioSample::slideVolume()
{
    if (!audioSink)
        return;

    qreal current = audioSink->volume();
    qreal diff = current - volume;
    if (diff>0.1)         current -= 0.1;
    else if (diff<-0.02)  current += 0.1;
    else
    {
        current = volume;
        killTimer(slideVolumeTimerId);
        slideVolumeTimerId=0;
    }
    audioSink->setVolume( current);
    qDebug() << " slideVolume: " << current;
}

void AudioSample::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)
    slideVolume();
}
