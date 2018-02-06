#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "ModelManager.h"
#include "TextureManager.h"
#include "Shader.h"
#include <QMap>
#include "Randomizer.h"
#include "DPIHelper.h"
#include <time.h>

class Graphics
{
public:
    static ViewPort         Screen;
    static DPIHelper        DPI;

    static ModelManager     Model;
    static TextureManager   Texture;
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
    }

private:
    Graphics();
};

#endif // GRAPHICS_H
