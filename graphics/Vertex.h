#ifndef _R1X_VERTEX_H
#define _R1X_VERTEX_H
#include <QVector2D>
#include <QVector3D>
#include <QDebug>

struct Vertex
{
    Vertex()
        : Position(0,0,0)
        , TextureCoordinate(0,0)
        , Normal(0,0,0)
    {}

    Vertex(QVector3D pos, QVector2D texCoord, QVector3D normal)
        : Position(pos)
        , TextureCoordinate(texCoord)
        , Normal(normal)
    {}

    QVector3D Position;
    QVector2D TextureCoordinate;
    QVector3D Normal;
};

QDebug operator<<(QDebug dbg, const Vertex &v);

typedef std::vector<QVector2D>  Vec2Array;
typedef std::vector<QVector3D>  Vec3Array;
typedef std::vector<Vertex>     VertArray;
typedef std::vector<unsigned short>   IndicesArray; // glES 2. only allows short indices

#endif // _R1X_VERTEX_H
