#ifndef AUDIOSAMPLE_H
#define AUDIOSAMPLE_H
#include "WavBuffer.h"
#include <QAudioSink>
#include <QAudioDevice>

class AudioSample : public QIODevice
{
    Q_OBJECT
public:
    AudioSample(QObject* parent, WavBuffer* wavBuffer);
    ~AudioSample();

    void Start();
    void Stop();
    bool isPlaying();
    bool isStoped();

    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);
    qint64 bytesAvailable() const;

    void Loop(bool value);
    bool isLooping() const;

    void    SetVolume(qreal vol);
    qreal   GetVolume();

    QString path();

    QAudioDevice& getDevice();
    void setDevice(const QAudioDevice &value);

private:
    WavBuffer           *buffer;
    QAudioSink          *audioSink;
    QAudioDevice        device;
    QAudioFormat        format;

    qint64      bytePosition;
    bool        looping;
    qreal       volume;
    qint64      volumeSlideTick;

    void    extractFormatFromWav(QAudioFormat &format, WavBuffer* wav);
    QAudioFormat::SampleFormat bitsToAudioFormat(int bits);

private slots:
    void AudioStateChanged(QAudio::State newState);
    void slideVolume();
};

#endif // AUDIOSAMPLE_H
