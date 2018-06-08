#include "AudioManager.h"
#include <QDebug>


AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
    for(WavBufferPtr buffer : soundBuffers)
        buffer->deleteLater();
    soundBuffers.clear();
}

AudioSamplePtr AudioManager::PlayAndForget(QObject *parent, QString name, bool loop)
{
    AudioSamplePtr audio = new AudioSample( parent, Get(name));
    audio->Loop(loop);
    audio->Start();
    playingSamples.append( audio );
    qDebug() << "active Sounds : " << playingSamples.size();
}

void AudioManager::RegularCleanup()
{
    QList<AudioSamplePtr>::iterator itr = playingSamples.begin();
    while (itr!=playingSamples.end())
    {
        AudioSamplePtr audio = (*itr);
        if (audio->isStoped())
        {
            audio->deleteLater();
            itr = playingSamples.erase(itr);
            qDebug() << "active Sounds : " << playingSamples.size();
        }
        else
            ++itr;
    }
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
