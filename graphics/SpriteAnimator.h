#ifndef _TEXTURE_ANIM_
#define _TEXTURE_ANIM_
#include "Temporal.h"
#include "UVRectArray.h"
#include "SampledCurve.h"
#include "Sprite.h"

class SpriteAnimator : public Temporal
{
public:
    SpriteAnimator(Sprite* target, UVRectArray* frames);
    virtual ~SpriteAnimator();

    void Repeat(int numRepeats=-1);

    // Temporal interface
    virtual void Update(float dt);
    bool Completed();

    void SetFrames(UVRectArray *frames);
    void SetPath(SampledCurve *path);

private:
    UVRectArray *uvFrames;
    SampledCurve *posFrames;

    Sprite      *Target;
    int         repetitions;

    int		currentFrame();
    int     lastFrameIndex;
};

#endif
