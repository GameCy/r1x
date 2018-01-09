#include "Graphics.h"

ViewPort       Graphics::Screen;
DPIHelper      Graphics::DPI;

ModelManager   Graphics::Model;
TextureManager Graphics::Texture;
ShaderPtr      Graphics::phongShader=0;

Graphics::Graphics()
{
}
