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

Sprite* Sprite::CloneFrom(Sprite *other)
{
    Pos = other->Pos;
    Size = other->Size;
    Color = other->Color;
    uvRect = other->uvRect;
    isVisible = other->isVisible;
    hasChanged = true;
}
