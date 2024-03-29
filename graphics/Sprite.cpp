#include "Sprite.h"
#include <cmath>

Sprite::Sprite()
    : RotationAngle(0)
    , Color(255,255,255,255)
    , uvRect()
    , isVisible(true)
    , deleteLater(false)
{
}

Sprite::Sprite(UVRect _uvRect)
    : RotationAngle(0)
    , Color(255,255,255,255)
    , uvRect(_uvRect)
    , isVisible(true)
    , deleteLater(false)
{
    Size = QVector2D(0,0);
    hasChanged = true;
}

Sprite::~Sprite()
{
}

void Sprite::SetVisible(bool visible)
{
    if (isVisible != visible)
    {
        isVisible = visible;
        hasChanged = true;
    }
}

QRectF Sprite::calcRect()
{
    return QRectF(Pos.toPoint(), (Pos+Size).toPointF());
}

void Sprite::CloneFrom(Sprite *other)
{
    Pos = other->Pos;
    RotationAngle = other->RotationAngle;
    RotationCenter = other->RotationCenter;
    Size = other->Size;
    Color = other->Color;
    uvRect = other->uvRect;
    isVisible = other->isVisible;
    hasChanged = true;
}
