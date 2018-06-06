#include "Sprite.h"
#include "SpriteAnimator.h"


Sprite::Sprite(UVRect _uvRect)
    : isVisible(true)
    , Color(255,255,255,255)
    , uvRect(_uvRect)
    , deleteLater(false)
    , animator(0)
{
    Size = QVector2D(0,0);
    hasChanged = true;
}

Sprite::~Sprite()
{
    if (animator)
        delete animator;
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

void Sprite::Animate(float duration, UVRectArray *frames, int numRepeats)
{
    if (!animator)
        animator = new SpriteAnimator(this, frames);
    else
        animator->SetFrames(frames);
    animator->Repeat(numRepeats);
    animator->Begin(duration);
}
