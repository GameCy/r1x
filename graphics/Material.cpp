#include "Material.h"
#include "Ogl.h"
#include "Graphics.h"

Material::Material()
    : texture(0)
    //, color(1,1,1,1)
    , blendSourceMode( GL_SRC_ALPHA)
    , blendDestMode(GL_ONE_MINUS_SRC_ALPHA)
    , Blending(false)
    , DepthTesting(true)
    , DepthWriting(true)
{
}

Material::Material(QString texturePath)
    : Material()
{
    LoadTexture(texturePath);
}

bool Material::LoadTexture(QString texturePath)
{
    texture = Graphics::Texture.Get(texturePath);
    return isTextureCreated();
}

bool    Material::isTextureCreated()
{
    return  (!!texture && texture->isCreated());
}

TexturePtr  Material::GetTexture()
{
    return texture;
}

void Material::SetTexture(TexturePtr tex)
{
    texture = tex;
}

void Material::Bind()
{
//    Graphics::phongShader->SetColorMask(color);

    if (!DepthTesting)
        ogl.glDisable(GL_DEPTH_TEST);
    if (!DepthWriting)
        ogl.glDepthMask(0);
    if (Blending)
    {
        ogl.glEnable(GL_BLEND);
        ogl.glBlendFunc(blendSourceMode, blendDestMode);
    }
    if (!!texture)
        texture->bind();
}

void Material::Unbind()
{
    if (!DepthTesting)
        ogl.glEnable(GL_DEPTH_TEST);
    if (!DepthWriting)
        ogl.glDepthMask(1);
    if (Blending)
        ogl.glDisable(GL_BLEND);

    //if (!!texture)        texture->unbind();
}
