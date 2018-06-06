#include "SpriteAnimator.h"
#include "QuadTypes.h"
#include <math.h>


SpriteAnimator::SpriteAnimator(Sprite *target, UVRectArray* frames)
    : uvFrames(frames)
    , Target(target)
    , lastFrameIndex(-1)
{
    TemporalPool::Add(this);
}

SpriteAnimator::~SpriteAnimator()
{
    TemporalPool::Remove(this);
}

void SpriteAnimator::Repeat(int numRepeats)
{
    repetitions = numRepeats;
}

void SpriteAnimator::Update(float dt)
{
    Temporal::Update(dt);

    if (IsFinished())
    {
        if (repetitions>0)
            --repetitions;
        if (repetitions!=0)
            Time=0;
    }

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

