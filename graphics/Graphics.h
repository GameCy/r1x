#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "ModelManager.h"
#include "TextureManager.h"
#include "PhongShader.h"
#include "RasterShader.h"
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
    static PhongShader*     phongShader;
    static RasterShader*    rasterShader;

    static bool Init()
    {
        phongShader = new PhongShader();
        rasterShader = new RasterShader();
        return phongShader->InitShaders() && rasterShader->InitShaders();
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
