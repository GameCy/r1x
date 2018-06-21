#ifndef _TEXTURE_ANIM_
#define _TEXTURE_ANIM_
#include "Temporal.h"
#include "UVRectArray.h"
#include "SampledCurve.h"
#include "Sprite.h"

class UVAnimator : public Temporal
{
public:
    UVAnimator(Sprite* target, UVRectArray* frames);
    virtual ~UVAnimator();

    void Repeat(int numRepeats=-1);

    // Temporal interface
    virtual void Update(float dt);

    bool CheckRepeats();
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
