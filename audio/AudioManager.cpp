#include "AudioManager.h"
#include <QDebug>


AudioManager::AudioManager()
{

}

AudioManager::~AudioManager()
{
    soundBuffers.clear();
}

WavBufferPtr AudioManager::Get(QString name)
{
    WavBufferPtr found;
    if (name.isEmpty())
        return 0;

    found = soundBuffers.value(name, 0);
    if (!found)
    {
        found = new WavBuffer;
        if (!found)
        {
            qDebug() << "failed to allocate memory for WavBuffer " << name;
            return 0;
        }
        if (!found->Load(name))
        {
            qDebug() << "failed to load " << name;
            return 0;
        }
        qDebug() << "Audio loaded " << name;

        soundBuffers[name] = found;
    }
    return found;
}

void AudioManager::Release(QString name)
{
    if (soundBuffers.contains(name))
        soundBuffers.remove(name);
}

void AudioManager::ClearAll()
{
    soundBuffers.clear();
}
