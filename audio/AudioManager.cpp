#include "AudioManager.h"
#include <QDebug>


AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
    for(WavBuffer* buffer : soundBuffers)
        buffer->deleteLater();
    soundBuffers.clear();
}

AudioSample* AudioManager::PlayAndForget(QObject *parent, QString name, bool loop)
{
    AudioSample* audio = new AudioSample( parent, Get(name));
    audio->Loop(loop);
    audio->Start();
    playingSamples.append( audio );
    qDebug() << "active Sounds : " << playingSamples.size();
    return audio;
}

void AudioManager::RegularCleanup()
{
    auto itr = playingSamples.begin();
    while (itr!=playingSamples.end())
    {
        AudioSample* audio = (*itr);
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

WavBuffer* AudioManager::Get(QString name)
{
    WavBuffer* found;
    if (name.isEmpty())
        return nullptr;

    found = soundBuffers.value(name, nullptr);
    if (!found)
    {
        found = new WavBuffer;
        if (!found)
        {
            qDebug() << "failed to allocate memory for WavBuffer " << name;
            return nullptr;
        }
        if (!found->Load(name))
        {
            qDebug() << "failed to load " << name;
            return nullptr;
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
    for(auto buffer : soundBuffers)
        delete buffer;
    soundBuffers.clear();
}
