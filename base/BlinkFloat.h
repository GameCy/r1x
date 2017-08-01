#ifndef BLINKFLOAT_H
#define BLINKFLOAT_H

class BlinkFloat
{
public:
    BlinkFloat(float start, float end, float period);

    void  Update(float dt);
    float Value();
    void SetNewTarget(float newTarget);

private:
    float startValue, endValue, duration;
    float current, t;
};

#endif // BLINKFLOAT_H
