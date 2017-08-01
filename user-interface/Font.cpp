#include "Font.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QUrl>
#include <QDir>


//===============================================

TextLabel::TextLabel(FontPtr font, QString txt, QVector2D pos)
    : Text(txt)
    , Position(pos)
    , FontRef(font)
    , Scale(1.0f)
{
    CalcLabelSize();
}

float TextLabel::getScale() const
{
    return Scale;
}

void TextLabel::setScale(float value)
{
    Scale = value;
    isDirty = true;
    CalcLabelSize();
}

void TextLabel::SetText(QString text)
{
    isDirty = true;
    Text = text;
    CalcLabelSize();
}

void TextLabel::SetPos(QVector2D pos)
{
    isDirty = true;
    Position = pos;
}

QVector2D TextLabel::GetPos()
{
    return Position;
}

void TextLabel::CalcLabelSize()
{
    float maxHeight=0;
    PixelWidth = 0;
    foreach (QChar ch, Text)
    {
        Symbol *symbol = FontRef->GetSymbolData( int(ch.toLatin1()) );
        if (symbol==0)
            continue;

        PixelWidth += symbol->xadvance;
        maxHeight = fmax( symbol->height, maxHeight);
    }
    PixelWidth *= Scale;
    PixelHeight = maxHeight*Scale;
}

//===============================================

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

Symbol *Font::GetSymbolData(int ch)
{
    SymbolsHash::iterator symbol = symbols.find(ch);
    if (symbol==symbols.end())
        return 0;
    return &(*symbol);
}

//===============================================

FontRenderer::FontRenderer(FontPtr font)
    : fontRef(font)
{
    quadRenderer = new QuadRenderer3D(2000, font->RasterMap);
}

void    FontRenderer::ClearAllLabels()
{
    labels.clear();
    quadRenderer->ClearQuads();
}

TextLabelPtr    FontRenderer::CreateLabel(QString text, QVector2D pos)
{
    TextLabelPtr label= new TextLabel(fontRef, text, pos);
    labels.push_back(label);
    return label;
}

void    FontRenderer::RemoveLabel(TextLabelPtr label)
{
    labels.removeAll(label);
}

void    FontRenderer::BuildQuads()
{
    int character=0;
    foreach (TextLabelPtr label, labels)
        character += label->Text.length();
    quadRenderer->ReserveActiveQuads(character);

    float texWidth = fontRef->RasterMap->GetTexture()->width();
    float texHeight = fontRef->RasterMap->GetTexture()->height();

    character=0;
    foreach (TextLabelPtr label, labels)
    {
        float xcursor = label->Position.x();
        float ycursor = label->Position.y();
        float scale = label->getScale();

        foreach (QChar ch, label->Text)
        {
            Symbol *symbol = fontRef->GetSymbolData( int(ch.toLatin1()) );
            if (symbol==0)
                continue;

            Quad3D &quad = quadRenderer->getQuad(character);
            symbol->CalcQuad( xcursor, ycursor, -2.0f, quad, texWidth, texHeight, scale);

            xcursor += symbol->xadvance * scale;
            character++;
        }
    }
    quadRenderer->UpdateQuadsBuffer(character);
}

void    FontRenderer::Render(CameraPtr camera)
{
    //camera.RasterMode(); // rasterMode called for all fonts once, from inside EntityManager
    quadRenderer->RenderQuads();
}

void	FontRenderer::Update(float dt)
{
    foreach (TextLabelPtr label,  labels)
    {
        if (label->isDirty)
        {
            BuildQuads();  // build all once and exit loop
            break;
        }
    }
}

bool	FontRenderer::IsFinished()  { return false; }
