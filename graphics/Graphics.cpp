#include "Graphics.h"

ViewPort       Graphics::Screen;
DPIHelper      Graphics::DPI;

ModelManager   Graphics::Model;
TextureManager Graphics::Texture;
PhongShader*   Graphics::phongShader=0;
RasterShader*  Graphics::rasterShader=0;

Graphics::Graphics()
{
}
