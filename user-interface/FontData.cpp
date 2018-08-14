#include "FontData.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QUrl>
#include <QDir>

JSonParser::JSonParser(QJsonObject *jsonParent)
    : parent(jsonParent)
{}

int     JSonParser::ReadInt(QString key, int defaultValue)
{
    QJsonValue val = parent->take(key);
    if (!val.isNull())
        return val.toInt(defaultValue);
    return defaultValue;
}

QString JSonParser::ReadString(QString key, QString defaultValue)
{
    QJsonValue val = parent->take(key);
    if (!val.isNull())
        return val.toString(defaultValue);
    return defaultValue;
}

FontConfig::FontConfig(QJsonObject *jsonConfig)
    : JSonParser(jsonConfig)
{
    name = ReadString("name", "AnonymousFont");
    textureFile = ReadString("textureFile", "no-path?");

    bold =   (ReadInt("bold",   0)==1)?true:false;
    italic = (ReadInt("italic", 0)==1)?true:false;
    smooth = (ReadInt("smooth", 0)==1)?true:false;

    size = ReadInt("size", 0);
    charHeight = ReadInt( "charHeight", 0);
    charSpacing = ReadInt("charSpacing", 0);
    lineSpacing = ReadInt("linespacing", 0);
    base = ReadInt("base", 0);

    textureHeight = ReadInt("textureHeight", -1);
    textureWidth = ReadInt("textureWidth", 0);
}


Symbol::Symbol(QJsonObject *jsonSymbol)
    :JSonParser(jsonSymbol)
{
    id = ReadInt("id", -1);
    x = ReadInt("x", 0);
    y = ReadInt("y", 0);
    width = ReadInt("width", 0);
    height= ReadInt("height", 0);
    xoffset = ReadInt("xoffset", 0);
    yoffset = ReadInt("yoffset", 0);
    xadvance = ReadInt("xadvance", 0);
}

void Symbol::CalcQuad(float xOffset, float yOffset, float z, Quad3D &quad, float texWidth, float texHeight, float scale)
{
    float W = width*scale;
    float H = height*scale;
    yOffset += yoffset*scale;

    quad.pos1 = QVector3D( xOffset   ,yOffset   ,z);
    quad.pos2 = QVector3D( xOffset+W ,yOffset   ,z);
    quad.pos3 = QVector3D( xOffset+W ,yOffset+H ,z);
    quad.pos4 = QVector3D( xOffset   ,yOffset+H ,z);
    quad.U1 = x/texWidth;         quad.V1 = (y+height)/texHeight;
    quad.U2 = (x+width)/texWidth; quad.V2 = (y+height)/texHeight;
    quad.U3 = (x+width)/texWidth; quad.V3 = y/texHeight;
    quad.U4 = x/texWidth;         quad.V4 = y/texHeight;
}
