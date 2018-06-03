#include "SpriteAnimator.h"
#include "QuadTypes.h"
#include <math.h>


SpriteAnimator::SpriteAnimator(Sprite *target, UVRectArray* frames)
    : uvFrames(frames)
    , Target(target)
    , lastFrameIndex(-1)
{
}

void SpriteAnimator::Update(float dt)
{
    Time += dt;

    int frameIndex = timeToIdx(Time);
    if (lastFrameIndex!=frameIndex)
    {
        Target->setUVRect( (*uvFrames)[ frameIndex ] );
    }
}

void SpriteAnimator::SetFrames(UVRectArray *frames)
{
    uvFrames = frames;
}

int		SpriteAnimator::timeToIdx(float time)
{
    if (time<0.f)   return 0;
    int maxElement = uvFrames->MaxElement;

    if (time>Duration) return maxElement-1;
    float ratio = time/Duration;
    int idx = (int) (ratio*float(maxElement));

    if (idx<0)              return 0;
    if (idx>=maxElement)    return maxElement-1;
	return idx;
}

