#ifndef TEXTLABEL_H
#define TEXTLABEL_H
#include "SmartPtr.h"
#include "Font.h"


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

    friend class TextRenderer;

private:
    TextLabel(FontPtr font, QString txt);
    QString     Text;
    QVector2D   Position;
    float       Scale;
    FontPtr     FontRef;
    bool        isDirty;

    void    CalcLabelSize();
};

typedef SmartPtr<TextLabel>     TextLabelPtr;

#endif // TEXTLABEL_H
