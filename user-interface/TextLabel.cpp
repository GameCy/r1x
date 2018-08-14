#include "TextLabel.h"
#include "Font.h"

TextLabel::TextLabel(FontPtr font, QString txt)
    : Text(txt)
    , Scale(1.0f)
    , FontRef(font)
    , isDirty(false)
    , toDelete(false)
{
    CalcLabelSize();
}

float TextLabel::getBaseline() const
{
    return Baseline;
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

void TextLabel::fitInsideBox(QVector2D box)
{
    float fitFactorDx = box.x() / PixelWidth;
    float fitFactorDy = box.y() / (PixelHeight +Baseline);
    setScale( Scale*fmin(fitFactorDx, fitFactorDy) );
}

void TextLabel::DeleteLater()
{
    toDelete=true;
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
    PixelWidth = 0;
    Baseline=999999.f;
    float topline=0;
    foreach (QChar ch, Text)
    {
        Symbol *symbol = FontRef->GetSymbolData(ch);
        if (symbol==nullptr)
            continue;

        PixelWidth += symbol->xadvance;

        if (Baseline>symbol->yoffset)   Baseline=symbol->yoffset;
        if (topline<(symbol->yoffset+symbol->height))
            topline = symbol->yoffset+symbol->height;
    }
    PixelWidth *= Scale;
    PixelHeight = Scale*(topline - Baseline); //Scale*FontRef->GetConfig()->charHeight;
    Baseline *= Scale;
}
