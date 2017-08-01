#ifndef ASSETS_H
#define ASSETS_H
#include "ModelManager.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "TextureAnimManager.h"
#include "AudioManager.h"
#include "Shader.h"
#include <QMap>
#include "Randomizer.h"
#include <time.h>

class Assets
{
public:
    static ModelManager     Model;
    static TextureManager   Texture;
    static TexAnimManager   TexAnim;
    static FontManager      Font;
    static AudioManager     Audio;
    static ShaderPtr        phongShader;

    static bool Init()
    {
        phongShader = new Shader();
        return phongShader->InitShaders();
    }

    static void DestroyAll()
    {
        if (phongShader)
        {
            phongShader->Destroy();
            delete phongShader;
            phongShader=0;
        }

        Model.ClearAll();
        Texture.ClearAll();
        TexAnim.ClearAll();
        Font.ClearAll();
        Audio.ClearAll();
    }

private:
    Assets();
};

#endif // ASSETS_H
