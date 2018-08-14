#ifndef TEXTLABEL_H
#define TEXTLABEL_H
#include "Font.h"

class TextLabel
{
public:
    void        SetText(QString text);
    void        SetPos(QVector2D pos);
    QVector2D   GetPos();

    float       getScale() const;
    void        setScale(float value);
    void        fitInsideBox(QVector2D box);
    float       getBaseline() const;

    void        DeleteLater();

    float       PixelWidth;
    float       PixelHeight;

    friend class TextRenderer;


private:
    TextLabel(FontPtr font, QString txt);
    QString     Text;
    QVector2D   Position;
    float       Scale;
    float       Baseline;
    FontPtr     FontRef;
    bool        isDirty;
    bool        toDelete;

    void    CalcLabelSize();
};

#endif // TEXTLABEL_H
