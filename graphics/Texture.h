#ifndef TEXTURE_H
#define TEXTURE_H
#include <QOpenGLTexture>
#include "SmartPtr.h"

class Texture : public QOpenGLTexture, public RefCountBase
{
public:
    Texture(const QImage &image, MipMapGeneration genMipMaps = GenerateMipMaps);
};

typedef SmartPtr<Texture>    TexturePtr;

#endif // TEXTURE_H
