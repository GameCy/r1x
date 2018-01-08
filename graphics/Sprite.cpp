#include "Sprite.h"


Sprite::Sprite(float width, float height, UVRect _uvRect)
    : isVisible(true)
    , uvRect(_uvRect)
{
    Size = QVector2D(width, height);
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

void Sprite::ClearChangedFlag()
{
    hasChanged = false;
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

