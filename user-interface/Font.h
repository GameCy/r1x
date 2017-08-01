#ifndef FONT_H
#define FONT_H
#include "FontData.h"
#include <QHash>
#include "Material.h"
#include "QuadRenderer3D.h"
#include "SmartPtr.h"
#include "Font.h"
#include "Entity.h"

class TextLabel;
typedef SmartPtr<TextLabel>     TextLabelPtr;

//-----------------------------------

class Font : public RefCountBase
{
public:
    Font(QString filepath);

    Symbol *GetSymbolData(int ch);

    MaterialPtr     RasterMap;

private:
    bool    LoadTexture();

    QString     fileName;
    FontConfig *config;
    QHash<int, Symbol> symbols;
};

typedef SmartPtr<Font>  FontPtr;

//------------------------------------

class FontRenderer : public Entity
{
public:
    FontRenderer(FontPtr font);

    void    ClearAllLabels();
    TextLabelPtr CreateLabel(QString text, QVector2D pos);
    void    RemoveLabel(TextLabelPtr label);

    void    BuildQuads();

    virtual void	Render(CameraPtr camera);
    virtual void	Update(float dt);
    virtual bool	IsFinished();

private:
    QList<TextLabelPtr> labels;
    QuadRenderer3D      *quadRenderer;
    FontPtr             fontRef;
};

typedef SmartPtr<FontRenderer> FontRendererPtr;
//typedef FontRenderer* FontRendererPtr;

//------------------------------------

class TextLabel : public RefCountBase
{
public:
    void        SetText(QString text);
    void        SetPos(QVector2D pos);
    QVector2D   GetPos();

    float       getScale() const;
    void        setScale(float value);

    float       PixelWidth;
    float       PixelHeight;

    friend class FontRenderer;

private:
    TextLabel(FontPtr font, QString txt, QVector2D pos);
    QString     Text;
    QVector2D   Position;
    float       Scale;
    FontPtr     FontRef;
    bool        isDirty;

    void    CalcLabelSize();
};


#endif // FONT_H
