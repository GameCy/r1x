#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H
#include "WavBuffer.h"
#include <QMap>


class AudioManager
{
public:
    AudioManager();
    ~AudioManager();

    WavBufferPtr Get(QString name);
    void       Release(QString name);

    void       ClearAll();

private:
    QMap<QString, WavBufferPtr>   soundBuffers;
};

#endif // AUDIOMANAGER_H

