#ifndef UVRECT_H
#define UVRECT_H

struct UVRect
{
    UVRect();
    UVRect(float u1, float v1, float u2, float v2);

    void Normalize(float nx, float ny);

    float U1,V1,U2,V2;
};

#endif // UVRECT_H
