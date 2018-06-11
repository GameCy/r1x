#include "SpriteAnimator.h"
#include "QuadTypes.h"
#include <math.h>


SpriteAnimator::SpriteAnimator(Sprite *target, UVRectArray* frames)
    : uvFrames(frames)
    , posFrames(0)
    , Target(target)
    , lastFrameIndex(-1)
    , repetitions(1)
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
    if (IsFinished() && Completed())
    {
        //Parent->Report Completed
        return;
    }

    if (uvFrames)
    {
        int uvFrameIndex = currentFrame();
        if (lastFrameIndex!=uvFrameIndex)
            Target->setUVRect( (*uvFrames)[ uvFrameIndex ] );
    }
    if (posFrames)
    {
        auto newPos = posFrames->GetPoint(Time);
        Target->setPos( newPos.toVector2D() );
    }
}

bool SpriteAnimator::Completed()
{
    if (repetitions>0)
        --repetitions;
    if (repetitions==0)
        return true; // completed, remove
    Time=0;
    return false; // not completed, keep it
}

void SpriteAnimator::SetFrames(UVRectArray *frames)
{
    uvFrames = frames;
}

void SpriteAnimator::SetPath(SampledCurve *path)
{
    posFrames = path;
}

int		SpriteAnimator::currentFrame()
{
    if (Time<0.f)   return 0;
    int maxElement = uvFrames->MaxElement;

    if (Time>Duration) return maxElement-1;
    float ratio = Time/Duration;
    int idx = (int) (ratio*float(maxElement));
	return idx;
}

