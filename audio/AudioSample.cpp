#include "AudioSample.h"
#include <qmath.h>
#include <qendian.h>
#include <QDebug>

AudioSample::AudioSample(QObject *parent, WavBufferPtr wavBuffer)
    : QIODevice(parent)
    , buffer(wavBuffer)
    , audioOutput(0)
    , bytePosition(0)
    , looping(false)
    , volume(0.8)
    , device(QAudioDeviceInfo::defaultOutputDevice())
{
    extractFormatFromWav( format, buffer );

    QAudioDeviceInfo info(device);
    if (!info.isFormatSupported(format))
    {
        qWarning() << "Default format not supported - trying to use nearest";
        format = info.nearestFormat(format);
    }
    audioOutput = new QAudioOutput(device, format, this);
    connect(audioOutput, &QAudioOutput::stateChanged, this, &AudioSample::AudioStateChanged);
    open(QIODevice::ReadOnly);
//    SetVolume(0);
}

AudioSample::~AudioSample()
{
    if (audioOutput)
        audioOutput->disconnect(this);
    if (this->isOpen())
        close();
    audioOutput->deleteLater();
}

void AudioSample::Pause()
{
    if (isPlaying())
        audioOutput->suspend();
}

void AudioSample::Resume()
{
    if ( (audioOutput->state() == QAudio::SuspendedState)
         || (audioOutput->state() == QAudio::StoppedState) )
        audioOutput->resume();
}

bool AudioSample::isPlaying()            { return (audioOutput->state() == QAudio::ActiveState); }

bool AudioSample::isStoped()             { return (audioOutput->state() == QAudio::StoppedState); }

bool AudioSample::isPaused()             { return (audioOutput->state() == QAudio::SuspendedState); }

void AudioSample::Loop(bool value)       { looping = value; }

bool AudioSample::isLooping() const      { return looping; }


void AudioSample::Start()
{
    if (isOpen())
    {
        bytePosition=0;
        audioOutput->reset();
        audioOutput->setVolume(0.0);
        audioOutput->start(this);
        audioOutput->setNotifyInterval(1);
        connect(audioOutput, &QAudioOutput::notify, this, &AudioSample::slideVolume);
    }
}

void AudioSample::Stop()
{
    bytePosition = 0;
    audioOutput->reset();
    audioOutput->stop();
}

qint64 AudioSample::readData(char *data, qint64 maxlen)
{
    if (buffer->size()==0)
        return 0;
    if (bytePosition>=buffer->size() )
    {
        if (looping)
            bytePosition = 0;
        else
            return 0;
    }

    const qint64 chunk = qMin(maxlen, (buffer->size() - bytePosition) );
    if (chunk<0)
        return 0;

    memcpy(data, buffer->data().constData() + bytePosition, chunk);
    bytePosition = bytePosition + chunk;
    return chunk;
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
    audioOutput->setNotifyInterval(1);
}

qreal AudioSample::GetVolume()
{
    return audioOutput->volume();
}

QAudioDeviceInfo AudioSample::getDevice() const
{
    return device;
}

void AudioSample::setDevice(const QAudioDeviceInfo &value)
{
    device = value;
}

void AudioSample::extractFormatFromWav(QAudioFormat &format, WavBufferPtr wav)
{
    format.setSampleRate( wav->sampleRate() );
    format.setChannelCount( wav->channelsCount() );
    format.setSampleSize( wav->bitDepth());
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);
}

void AudioSample::AudioStateChanged(QAudio::State newState)
{
    qDebug() << "audio state " << newState;
    if ( (newState==QAudio::IdleState)
         && bytePosition>=buffer->size()
         && (!looping) )
    {
        Stop();
    }
}

void AudioSample::slideVolume()
{
    qreal current = audioOutput->volume();
    qreal diff = current - volume;
    if (diff>0.02)
    {
        audioOutput->setVolume( current - 0.02);
    }
    else if (diff<-0.02)
    {
        audioOutput->setVolume( current + 0.02);
    }
    else
    {
        audioOutput->setNotifyInterval(50);
    }
}
