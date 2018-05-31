#include "Sprite.h"


Sprite::Sprite(UVRect _uvRect)
    : isVisible(true)
    , Color(255,255,255,255)
    , uvRect(_uvRect)
    , deleteLater(false)
{
    Size = QVector2D(0,0);
    hasChanged = true;
}

void Sprite::SetVisible(bool visible)
{
    if (isVisible != visible)
    {
        isVisible = visible;
        hasChanged = true;
    }
}

bool Sprite::IsVisible()
{
    return isVisible;
}

QVector2D Sprite::getPos() const
{
    return Pos;
}

void Sprite::setPos(const QVector2D &value)
{
    Pos = value;
    hasChanged = true;
}

QVector2D Sprite::getSize() const
{
    return Size;
}

void Sprite::setSize(const QVector2D &value)
{
    Size = value;
    hasChanged = true;
}

QColor Sprite::getColor() const
{
    return Color;
}

void Sprite::setColor(const QColor &value)
{
    Color = value;
    hasChanged = true;
}

void Sprite::ClearChangedFlag()
{
    hasChanged = false;
}

void Sprite::DeleteLater()
{
    deleteLater=true;
}

UVRect& Sprite::getUVRect()
{
    return uvRect;
}

void Sprite::setUVRect(const UVRect &value)
{
    uvRect = value;
    hasChanged = true;
}

Sprite* Sprite::CloneFrom(Sprite *other)
{
    Pos = other->Pos;
    Size = other->Size;
    Color = other->Color;
    uvRect = other->uvRect;
    isVisible = other->isVisible;
    hasChanged = true;
}
