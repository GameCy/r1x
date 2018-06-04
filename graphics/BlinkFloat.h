#ifndef BLINKFLOAT_H
#define BLINKFLOAT_H

class BlinkFloat
{
public:
    BlinkFloat(float start, float end, float period);

    void    Update(float dt);
    bool    hasEnded();

    float   Value();
    void    SetNewTarget(float newTarget);
    void    Repeat(int _repetitions);

private:
    float   startValue, endValue, duration;
    float   current, t;
    int     repetitions;
};

#endif // BLINKFLOAT_H
