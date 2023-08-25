#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "ModelManager.h"
#include "TextureManager.h"
#include "PhongShader.h"
#include "RasterShader.h"
#include <QMap>
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

#define SNorm(NX,NY) Graphics::Screen.Normalized(NX, NY)

// DX is a percentage of the whole width,
// VY_RELATIVE is a percentage of DX.
// E.g. VY_RELATIVE = 1 will always result in visualy square sizes.
#define XNormYRatio(NX,VY_RELATIVE)  Graphics::DPI.VisualSize(NX, VY_RELATIVE, true)
#define YNormXRatio(NY,VX_RELATIVE)  Graphics::DPI.VisualSize(NY, VX_RELATIVE, false)

#endif // GRAPHICS_H
