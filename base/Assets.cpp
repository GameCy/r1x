#include "Assets.h"

ModelManager   Assets::Model;
TextureManager Assets::Texture;
FontManager    Assets::Font;
AudioManager   Assets::Audio;
ShaderPtr      Assets::phongShader=0;

Assets::Assets()
{
}
