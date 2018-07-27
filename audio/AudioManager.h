#ifndef SAMPLEPOOL_H
#define SAMPLEPOOL_H
#include "WavBuffer.h"
#include <QMap>
#include <QList>
#include "AudioSample.h"

class AudioManager
{
public:
    AudioManager();
    ~AudioManager();

    AudioSample *PlayAndForget(QObject *parent, QString name, bool loop=false);
    void         RegularCleanup();

    WavBuffer   *Get(QString name);
    void         Release(QString name);

    void         ClearAll();

private:
    QMap<QString, WavBuffer*>   soundBuffers;
    QList<AudioSample*>       playingSamples;
};

#endif // SAMPLEPOOL_H

