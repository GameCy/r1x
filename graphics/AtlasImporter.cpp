#include "AtlasImporter.h"
#include <QFile>
#include <QTextStream>

AtlasImporter::AtlasImporter()
    : PixelWidth(0)
    , PixelHeight(0)
    , normalizedCoords(false)
{
}

AtlasImporter::AtlasImporter(QString path, bool normalized)
    : PixelWidth(0)
    , PixelHeight(0)
{
    Load(path, normalized);
}

bool AtlasImporter::Load(QString path, bool normalized)
{
    normalizedCoords = normalized;
    QFile file(path);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        ParseHeader(stream.readLine(200));
        stream.readLine();  // skip empty line

        while (!stream.atEnd())
        {
            ParseLine(stream.readLine(200));
        }
        file.close();
        return IsValid();
    }
    return false;
}

bool AtlasImporter::IsValid()
{
    return ( (!TexFileName.isEmpty())
             && (PixelWidth>0)
             && (PixelHeight>0)
             && (UVRectMap.size()>0) );
}

bool AtlasImporter::GetUVRect(QString spriteName, UVRect &uvRect)
{
    QMap<QString,UVRect>::iterator rectItr = UVRectMap.find(spriteName);
    if (rectItr==UVRectMap.end())
        return false;
    uvRect = UVRect(*rectItr);
    return true;
}

void AtlasImporter::ParseHeader(QString line)
{
    QStringList items = line.split(",");
    if (items.size()<3)
        return;

    TexFileName = items[0];
    PixelWidth = items[1].toInt();
    PixelHeight = items[2].toInt();
}

void AtlasImporter::ParseLine(QString line)
{
    QStringList items = line.split(",");
    if (items.size()<5)
        return;
    float u1 = items[1].toFloat();
    float v1 = items[2].toFloat();
    UVRect rect( u1, v1, u1 + items[3].toFloat() -1.0f, v1 + items[4].toFloat() -1.0f);
    if (normalizedCoords)
        rect.Normalize(float(PixelWidth), float(PixelHeight));
    UVRectMap.insert(items[0], rect);
}
