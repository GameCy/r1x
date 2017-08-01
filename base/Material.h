#ifndef MATERIAL_H
#define MATERIAL_H
#include <QVector4D>
#include "Texture.h"

class Material : public RefCountBase
{
public:
    Material();
    Material(QString texturePath);

    bool    LoadTexture(QString texturePath);
    bool    isTextureCreated();
    void    Bind();
    void    Unbind();
    TexturePtr GetTexture();
    void    SetTexture(TexturePtr tex);

    //QVector4D       color;
    GLuint          blendSourceMode;
    GLuint          blendDestMode;
    bool            Blending;
    bool            DepthTesting;
    bool            DepthWriting;

private:
    TexturePtr      texture;
};

typedef	SmartPtr<Material>	MaterialPtr;

#endif // MATERIAL_H
