#ifndef MATERIAL_H
#define MATERIAL_H
#include <QOpenGLTexture>
#include <QVector4D>

class Material
{
public:
    Material();


    QOpenGLTexture *texture;
    QVector4D       color;
    GLuint          blendMode;
    GLuint          alphaMode;
};

#endif // MATERIAL_H
