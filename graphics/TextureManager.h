#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "Texture.h"
#include <QMap>
#include "UVAnimator.h"

const QString Tex_Shadow(":/textures/fakeshadow.png");
const QString Tex_Smoke(":/textures/smokeAnim.png");
const QString Tex_SparkleVertical(":/textures/SparkleVertical.png");

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

    TexturePtr Get(QString name);
    void       Release(QString name);

    void       ClearAll();

private:
    QMap<QString, TexturePtr>   textures;
};

#endif // TEXTUREMANAGER_H

