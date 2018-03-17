#ifndef SPRITEMAP_H
#define SPRITEMAP_H
#include "SmartPtr.h"
#include "Sprite.h"
#include "AtlasImporter.h"
#include <QVector2D>
#include <vector>
#include "Material.h"
#include "QuadRenderers.h"

class SpriteMap : public RefCountBase
{
public:
    // path = path to atlas or texture
    SpriteMap(int maxQuads, QString path, bool useColorPerSprite=false);
    ~SpriteMap();

    Sprite*     CreateSprite(QString spriteName);
    bool        DestroySprite(Sprite* sprite);

    MaterialPtr GetMaterial();
    MaterialPtr LoadMaterial(QString path);
    bool        GetUVRect(QString spriteName, UVRect &uvRect);

    void Render();
    void Update();


private:
    QVector<Sprite*>    sprites;
    QuadRendererBase*   renderer;
    AtlasImporter       atlas;
    bool                colorPerSprite;

    void    BuildQuads();
    int     CountVisibleSprites();
    void    SetQuad2D(Sprite* spr, int quadIndex);
    void    SetQuad2DX(Sprite* spr, int quadIndex);
};

typedef SmartPtr<SpriteMap>     SpriteMapPtr;
//typedef SpriteMap*     SpriteMapPtr;

#endif // SPRITEMAP_H
