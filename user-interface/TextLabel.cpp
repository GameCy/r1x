#include "TextLabel.h"
#include "Font.h"

TextLabel::TextLabel(FontPtr font, QString txt)
    : Text(txt)
    , FontRef(font)
    , Scale(1.0f)
    , isDirty(false)
    , toDelete(false)
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
