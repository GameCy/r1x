#ifndef TEXTUREANIMMANAGER_H
#define TEXTUREANIMMANAGER_H
#include <QVector>
#include "UVAnim.h"
#include "TextureManager.h"

//enum TexAnimNames {
//    TexAnim_Smoke,
//    TexAnim_SparkleVertical,
//    TexAnim_MAX_ID
//};


//const TexAnimParams animParams[] = {
//    { Tex_Smoke, 0.8f, 2, 2, 4 },
//    { Tex_SparkleVertical, 0.8f, 4, 2, 8 }
//};


class TexAnimManager
{
public:
    TexAnimManager();
    ~TexAnimManager();

    //TextureAnimPtr Get(TexAnimNames name);
    //void       Release(TexAnimNames name);

    void ClearAll();

private:
    //QVector<UVAnim?*?>   texAnims;
};

#endif // TEXTUREANIMMANAGER_H
