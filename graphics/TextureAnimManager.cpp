#include "TextureAnimManager.h"
#include <QDebug>


TexAnimManager::TexAnimManager()
{
    texAnims.clear();
    //for(int i=0; i<TexAnim_MAX_ID; ++i)
    {
        texAnims.push_back(0);
    }
}

TexAnimManager::~TexAnimManager()
{
    texAnims.clear();
}

//TextureAnimPtr TexAnimManager::Get(TexAnimNames name)
//{
//    if (name<0 || name>=TexAnim_MAX_ID)
//        return 0;
//    if (texAnims[name]==0)
//    {
//        texAnims[name] = new UVAnim( animParams[name] );
//    }
//    return texAnims[name];
//}

//void TexAnimManager::Release(TexAnimNames name)
//{
//    if (name>=0 && name<TexAnim_MAX_ID && (texAnims[name]!=0) )
//    {
//        texAnims[name] = 0;
//    }
//}

void TexAnimManager::ClearAll()
{
    texAnims.clear();
}

