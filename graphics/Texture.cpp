#include "Texture.h"


Texture::Texture(const QImage &image, QOpenGLTexture::MipMapGeneration genMipMaps)
    : QOpenGLTexture(image, genMipMaps)
{
}
