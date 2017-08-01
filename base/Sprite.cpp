#include "Sprite.h"


Sprite::Sprite(float width, float height, float u1, float v1, float u2, float v2)
    : isVisible(true)
{
    UVstart = QVector2D(u1,v1);
    UVsize = QVector2D(u2,v2);

    Size = QVector2D(width, height);
    hasChanged = true;
}

Sprite::Sprite(float width, float height, UVRect uvs)
    : isVisible(true)
{
    UVstart = QVector2D(uvs.U1, uvs.V1);
    UVsize = QVector2D(uvs.U2- uvs.U1, uvs.V2- uvs.V1);

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

QVector2D Sprite::getUVstart() const
{
    return UVstart;
}

void Sprite::setUVstart(const QVector2D &value)
{
    UVstart = value;
    hasChanged = true;
}

QVector2D Sprite::getUVsize() const
{
    return UVsize;
}

void Sprite::setUVsize(const QVector2D &value)
{
    UVsize = value;
    hasChanged = true;
}

void Sprite::ClearChangedFlag()
{
    hasChanged = false;
}

