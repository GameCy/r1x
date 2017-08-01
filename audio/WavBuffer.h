#ifndef WAVBUFFER_H
#define WAVBUFFER_H

#include <QBuffer>
#include <QString>
#include <QVector>


class WavBuffer : public QBuffer
{
    Q_OBJECT
    
public:
    // Getters
    qint64    audioSize()      { return m_audioSize; }
    qint64    framesCount()    { return m_framesCount; }
    qint64    sampleRate()     { return m_sampleRate; }
    int     bitDepth()       { return m_bitDepth; }
    int     bytesPerSample() { return m_bytesPerSample; }
    int     bytesPerFrame()  { return m_bytesPerFrame; }
    int     channelsCount()  { return m_channelsCount; }
    QString filePath()       { return m_filePath; }
    const char* error()      { return m_error; }
    
    bool Load(QString filePath);
    
    int getSample(int frameNumber, int channelNumber);
    void getMinMaxSampleValueInRange(int startFrame, int range, int channelIndex, int& min, int&max);
    
    void cutBlock(uint startFrame, uint endFrame);
    void setAudioSize(int framesCount);
    
private:
    qint64 m_audioSize;
    qint64 m_framesCount;
    qint64 m_sampleRate;
    int m_bitDepth;
    int m_bytesPerSample;
    int m_bytesPerFrame;
    int m_channelsCount;
    QString     m_filePath = "";  // Contains the path to the audio WAV file
    const char *m_error    = "";  // Contains the error message of the last error
    
    int getByte(int index);

    
    bool headerIsValid(const QByteArray&);
    void ReadHeader();
};

typedef WavBuffer*  WavBufferPtr;
//typedef SmatPtr<WavBuffer>  WavBufferPtr;

#endif // WAVBUFFER_H
