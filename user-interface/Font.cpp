#include "Font.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QUrl>
#include <QDir>

Font::Font(QString filepath)
    : RasterMap(0)
    , fileName(filepath)
    , config(0)
{
    QFile file(filepath);
    if (file.open(QIODevice::ReadOnly))
    {
        QString fileContents = file.readAll();
        QJsonParseError parseError;
        QJsonDocument jsonDocument = QJsonDocument::fromJson( fileContents.toUtf8(), &parseError );
        if (parseError.error!=QJsonParseError::NoError)
        {
            qDebug() << "Error parsing font file: " << filepath << "Error=" << parseError.errorString();
            return;
        }
        QJsonObject root = jsonDocument.object();

        // parse config
        QJsonObject::iterator atConfig = root.find("config");
        if (atConfig==root.end())
        {
            qDebug() << "could not parse font config: " << filepath;
            return;
        }
        QJsonObject jsonConfig = atConfig.value().toObject();
        config = new FontConfig( &jsonConfig );

        // parse symbols
        QJsonObject::iterator atSymbols = root.find("symbols");
        if (atSymbols==root.end())
        {
            qDebug() << "could not parse font symbols: " << filepath;
            return;
        }
        QJsonArray array = atSymbols.value().toArray();
        foreach (const QJsonValue symbol, array)  {
            QJsonObject jsonSymbol = symbol.toObject();
            Symbol newSymbol( &jsonSymbol );
            symbols.insert(newSymbol.id, newSymbol);
        }

        if (!LoadTexture())
        {
            qDebug() << "font texture not created: " << config->textureFile;
        }
        symbolsGLNormalizeYOffset();
    }
}


bool    Font::LoadTexture()
{
    QFileInfo info(fileName);

    QString texturePath( info.absolutePath() );
    texturePath.append( QDir::separator() ).append(config->textureFile);

    RasterMap = new Material( texturePath);
    RasterMap->DepthTesting = false;
    RasterMap->DepthWriting = false;
    RasterMap->Blending = true;

    return (!!RasterMap) && RasterMap->isTextureCreated();
}

void Font::symbolsGLNormalizeYOffset()
{
    if (!config)
        return;
    float fontHeight = config->charHeight;
    for(Symbol &sym:symbols)
        sym.yoffset = fontHeight - sym.yoffset - sym.height;
}

Symbol *Font::GetSymbolData(QChar ch)
{
    int charID = ch.unicode(); //ch.toLatin1();
    SymbolsHash::iterator symbol = symbols.find(charID);
    if (symbol==symbols.end())
        return 0;
    return &(*symbol);
}
// greek mapping starts at:
/*
ushort index = ch.unicode();
if (index>0x03A1)
     --index;
return index - 0x0391;
*/
