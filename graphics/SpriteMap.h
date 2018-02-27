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
    SpriteMap(int maxQuads, bool perVertexColor, QString atlasPath);
    ~SpriteMap();

    Sprite*     CreateSprite(QString spriteName);
    bool        DestroySprite(Sprite* sprite);

    MaterialPtr GetMaterial();
    bool        GetUVRect(QString spriteName, UVRect &uvRect);

    void Render();
    void Update();

private:
    bool                usePerVertexColor;
    QVector<Sprite*>    sprites;
    QuadRenderer2D      renderer;
    AtlasImporter       atlas;

    void    BuildQuads2D();
    void    BuildQuads2DX();
    int     CountVisibleSprites();

};

typedef SmartPtr<SpriteMap>     SpriteMapPtr;
//typedef SpriteMap*     SpriteMapPtr;

#endif // SPRITEMAP_H
