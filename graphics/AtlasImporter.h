#ifndef ATLASIMPORTER_H
#define ATLASIMPORTER_H
#include <QString>
#include <QMap>
#include "UVRect.h"

class AtlasImporter
{
public:
    AtlasImporter();
    AtlasImporter(QString path, bool normalized);

    bool Load(QString path, bool normalized);
    bool IsValid();

    bool GetUVRect(QString spriteName, UVRect &uvRect);

    QString TexFileName;
    QMap<QString,UVRect>  UVRectMap;

    int PixelWidth;
    int PixelHeight;

private:
    void ParseHeader(QString line);
    void ParseLine(QString line);

    bool normalizedCoords;
};

#endif // ATLASIMPORTER_H
