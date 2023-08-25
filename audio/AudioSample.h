#ifndef AUDIOSAMPLE_H
#define AUDIOSAMPLE_H
#include "WavBuffer.h"
#include <QAudioOutput>

class AudioSample : public QIODevice
{
    Q_OBJECT
public:
    AudioSample(QObject* parent, WavBuffer* wavBuffer);
    ~AudioSample();

    void Start();
    void Stop();
    void Pause();
    void Resume();
    bool isPlaying();
    bool isStoped();
    bool isPaused();

    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);
    qint64 bytesAvailable() const;

    void Loop(bool value);
    bool isLooping() const;

    void    SetVolume(qreal vol);
    qreal   GetVolume();

    QString path();

    QAudioDeviceInfo getDevice() const;
    void setDevice(const QAudioDeviceInfo &value);

private:
    WavBuffer           *buffer;
    QAudioOutput        *audioOutput;
    QAudioDeviceInfo    device;
    QAudioFormat        format;

    qint64      bytePosition;
    bool        looping;
    qreal       volume;

    void    extractFormatFromWav(QAudioFormat &format, WavBuffer* wav);

private slots:
    void AudioStateChanged(QAudio::State newState);
    void slideVolume();
};

#endif // AUDIOSAMPLE_H
