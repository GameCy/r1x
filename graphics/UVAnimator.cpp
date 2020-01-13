#include "UVAnimator.h"
#include "QuadTypes.h"
#include <math.h>


UVAnimator::UVAnimator(Sprite *target, UVRectArray* frames)
    : uvFrames(frames)
    , posFrames(nullptr)
    , Target(target)
    , repetitions(1)
    , lastFrameIndex(-1)
{
    TemporalPool::Add(this);
}

UVAnimator::~UVAnimator()
{
    if (toDelete==false)
        TemporalPool::Remove(this);
}

void UVAnimator::Repeat(int numRepeats)
{
    repetitions = numRepeats;
}

void UVAnimator::Update(float dt)
{
    if (IsFinished() && CheckRepeats())
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

bool UVAnimator::CheckRepeats()
{
    if (repetitions>0)
        --repetitions;
    if (repetitions==0)
        return true; // completed, remove
    Time=0;
    return false; // not completed, keep it
}

void UVAnimator::SetFrames(UVRectArray *frames)
{
    uvFrames = frames;
}

void UVAnimator::SetPath(SampledCurve *path)
{
    posFrames = path;
}

int		UVAnimator::currentFrame()
{
    if (Time<0.f)   return 0;
    int maxElement = uvFrames->MaxElement;

    if (Time>Duration) return maxElement-1;
    float ratio = Time/Duration;
    int idx = int(ratio*float(maxElement));
	return idx;
}

