#ifndef TEXTUREANIMMANAGER_H
#define TEXTUREANIMMANAGER_H
#include <QVector>
#include "TextureAnim.h"
#include "TextureManager.h"

enum TexAnimNames {
    TexAnim_Smoke,
    TexAnim_Explosion,
    TexAnim_Flash,
    TexAnim_MAX_ID
};


const TexAnimParams animParams[] = {
    { Tex_Smoke, 0.8f, 2, 2, 4 },
    { "LASTONE", 0.0f, 0, 0, 0 }
};


class TexAnimManager
{
public:
    TexAnimManager();
    ~TexAnimManager();

    TextureAnimPtr Get(TexAnimNames name);
    void       Release(TexAnimNames name);

    void ClearAll();

private:
    QVector<TextureAnimPtr>   texAnims;
};

#endif // TEXTUREANIMMANAGER_H
