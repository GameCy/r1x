#ifndef QUADTYPES_H
#define QUADTYPES_H
#include <QVector2D>
#include <QVector3D>
#include <QColor>
#include "AtlasImporter.h"

struct Quad2D
{
    float       X1, Y1, U1, V1;
    float       X2, Y2, U2, V2;
    float       X3, Y3, U3, V3;
    float       X4, Y4, U4, V4;

    void    SetGeometry(float x, float y, float w, float h);
    void    SetUVs(float u1, float v1, float uvWidth, float uvHeight);
    void    SetUVRect(const UVRect &uvs);
};

struct Quad2DX
{
    float       X1, Y1, U1, V1, R1,G1,B1,A1;
    float       X2, Y2, U2, V2, R2,G2,B2,A2;
    float       X3, Y3, U3, V3, R3,G3,B3,A3;
    float       X4, Y4, U4, V4, R4,G4,B4,A4;

    void    SetGeometry(float x, float y, float w, float h);
    void    SetUVs(float u1, float v1, float uvWidth, float uvHeight);
    void    SetUVRect(const UVRect &uvs);
    void    SetAllColors(QColor color);
};

template<class QuadType>
void    RotateAndSetGeometry(QuadType &outQuad, QVector2D &point, QVector2D size, QVector2D &center, float angle)
{
  QVector2D p2(point.x()+size.x(), point.x());
  QVector2D p4(point.x(), point.y() + size.y());
  QVector2D p3 = point + size;

  float s = sinf(angle);
  float c = cosf(angle);

  // translate point to origin, then rotate, then translate to desired
  QVector2D to_origin = point - center;
  QVector2D rotated = center + QVector2D( to_origin.x()*c - to_origin.y()*s, to_origin.x()*s + to_origin.y()*c);
  outQuad.X1 = rotated.x();
  outQuad.Y1 = rotated.y();

  // same for p2
  to_origin = p2 - center;
  rotated = center + QVector2D( to_origin.x()*c - to_origin.y()*s, to_origin.x()*s + to_origin.y()*c);
  outQuad.X2 = rotated.x();
  outQuad.Y2 = rotated.y();

  // same for p3
  to_origin = p3 - center;
  rotated = center + QVector2D( to_origin.x()*c - to_origin.y()*s, to_origin.x()*s + to_origin.y()*c);
  outQuad.X3 = rotated.x();
  outQuad.Y3 = rotated.y();

  // same for p4
  to_origin = p4 - center;
  rotated = center + QVector2D( to_origin.x()*c - to_origin.y()*s, to_origin.x()*s + to_origin.y()*c);
  outQuad.X4 = rotated.x();
  outQuad.Y4 = rotated.y();
}


struct Quad3D
{
    QVector3D   pos1;
    float       U1, V1;
    QVector3D   pos2;
    float       U2, V2;
    QVector3D   pos3;
    float       U3, V3;
    QVector3D   pos4;
    float       U4, V4;

    void    SetUVs(float u1, float v1, float uvWidth, float uvHeight);
    void    SetUVRect(const UVRect &uvs);
};


struct QuadBufferSettings2D
{
    static const int attrib1Components= 2;
    static const int attrib2Components= 2;
    static const int attrib3Components= 0;
    static const int attrib2ByteOffset = 8;
    static const int attrib3ByteOffset = -1;
};

struct QuadBufferSettings2DX
{
    static const int attrib1Components= 2;
    static const int attrib2Components= 2;
    static const int attrib3Components= 4;
    static const int attrib2ByteOffset = 8;
    static const int attrib3ByteOffset = 16;
};
struct QuadBufferSettings3D
{
    static const int attrib1Components= 3;
    static const int attrib2Components= 2;
    static const int attrib3Components= 3;
    static const int attrib2ByteOffset = 12;
    static const int attrib3ByteOffset = 20;
};


struct Particle {
    QVector3D	pos;
    QVector3D	speed;
    float		t;
    unsigned short animFrameIndex;
};

typedef std::vector<Particle>   ParticleVec;

#endif // QUADTYPES_H
