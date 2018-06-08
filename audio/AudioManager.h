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

    AudioSamplePtr  PlayAndForget(QObject *parent, QString name, bool loop=false);
    void            RegularCleanup();

    WavBufferPtr    Get(QString name);
    void            Release(QString name);

    void       ClearAll();

private:
    QMap<QString, WavBufferPtr> soundBuffers;
    QList<AudioSamplePtr>       playingSamples;
};

#endif // SAMPLEPOOL_H

