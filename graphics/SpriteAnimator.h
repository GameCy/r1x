#ifndef _TEXTURE_ANIM_
#define _TEXTURE_ANIM_
#include "Temporal.h"
#include "UVRectArray.h"
#include "Sprite.h"

class SpriteAnimator : public Temporal
{
public:
    SpriteAnimator(Sprite* target, UVRectArray* frames);

    // Temporal interface
    virtual void Update(float dt);

    void SetFrames(UVRectArray *frames);

private:
    UVRectArray *uvFrames;
    Sprite      *Target;
    int         lastFrameIndex;

    int		timeToIdx(float time);
};

#endif
