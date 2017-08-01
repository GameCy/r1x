#ifndef FONTDATA_H
#define FONTDATA_H
#include <QJsonObject>
#include <QHash>
#include "QuadRenderer3D.h"

class JSonParser
{
protected:
    JSonParser(QJsonObject *jsonParent);

    int     ReadInt(QString key, int defaultValue);
    QString ReadString(QString key, QString defaultValue);

    QJsonObject *parent;
};

class FontConfig : protected JSonParser
{
public:
    FontConfig(QJsonObject *jsonConfig);

    QString name;
    QString textureFile;
    bool bold;
    bool italic;
    bool smooth;

    int size;
    int charHeight;
    int charSpacing;
    int lineSpacing;
    int base;

    int textureHeight;
    int textureWidth;

};

class Symbol : protected JSonParser
{
public:
    Symbol(QJsonObject *jsonSymbol);

    void CalcQuad(float xOffset, float yOffset, float z, Quad3D &quad, float texWidth, float texHeight, float scale);

    int id;
    float height;
    float width;
    float x;
    float y;
    float xadvance;
    float xoffset;
    float yoffset;
};

typedef QHash<int, Symbol> SymbolsHash;


#endif // FONTDATA_H
