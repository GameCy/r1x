#include "Vertex.h"

QDebug operator<<(QDebug dbg, const Vertex &v)
{
    dbg << "V(" << v.Position << ") tx(" << v.TextureCoordinate << ") N(" << v.Normal << ")\n";
    return dbg;
}
