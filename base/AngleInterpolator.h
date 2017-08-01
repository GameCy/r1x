#ifndef ANGLEINTERPOLATOR_H
#define ANGLEINTERPOLATOR_H

class AngleInterpolator
{
public:
    AngleInterpolator(bool degrees=false);

    bool Init(float start, float end, float speed);

    float GetCurrent();
    bool IsPositive();
    bool IsFinished();
    void SetNewTarget(float newTarget);
    void Update(float dt);

private:
    float current;
    float target;
    float speed;
    bool  positiveDirection;

    float HalfCircle;
    float FullCircle;
};

#endif // ANGLEINTERPOLATOR_H
