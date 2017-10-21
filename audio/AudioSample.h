#ifndef AUDIOSAMPLE_H
#define AUDIOSAMPLE_H
#include "WavBuffer.h"
#include <QAudioOutput>

class AudioSample : public QIODevice
{
    Q_OBJECT
public:
    AudioSample(QObject* parent, WavBufferPtr wavBuffer);
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

    QAudioDeviceInfo getDevice() const;
    void setDevice(const QAudioDeviceInfo &value);

private:
    WavBufferPtr        buffer;
    QAudioOutput        *audioOutput;
    QAudioDeviceInfo    device;
    QAudioFormat        format;

    qint64      bytePosition;
    bool        looping;
    qreal       volume;

    void    extractFormatFromWav(QAudioFormat &format, WavBufferPtr wav);

private slots:
    void AudioStateChanged(QAudio::State newState);
    void slideVolume();
};

typedef AudioSample*    AudioSamplePtr;

#endif // AUDIOSAMPLE_H
