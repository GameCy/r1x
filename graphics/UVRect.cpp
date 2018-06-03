#include "UVRect.h"

UVRect::UVRect()
{ U1=0; V1=0; U2=0; V2=0; }

UVRect::UVRect(float u1, float v1, float u2, float v2)
{ U1=u1; V1=v1; U2=u2; V2=v2; }

UVRect::UVRect(UVRect &other)
{ U1=other.U1; V1=other.V1; U2=other.U2; V2=other.V2; }

UVRect::UVRect(const UVRect &other)
{ U1=other.U1; V1=other.V1; U2=other.U2; V2=other.V2; }

void UVRect::Normalize(float nx, float ny)
{
    U1/= nx;  U2/=nx;
    V1/=ny;   V2/=ny;
}
