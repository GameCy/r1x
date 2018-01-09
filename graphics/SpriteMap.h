#ifndef SPRITEMAP_H
#define SPRITEMAP_H
#include "SmartPtr.h"
#include "Sprite.h"
#include "AtlasImporter.h"
#include <QVector2D>
#include <vector>
#include "Material.h"
#include "QuadRenderer2D.h"

class SpriteMap : public RefCountBase
{
public:
    SpriteMap(int maxQuads, QString atlasPath);
    ~SpriteMap();

    Sprite*     CreateSprite(QString spriteName, float width, float height);
    bool        DestroySprite(Sprite* sprite);

    MaterialPtr GetMaterial();
    bool        GetUVRect(QString spriteName, UVRect &uvRect);

    void Render();
    void Update();

private:
    QVector<Sprite*>    sprites;
    QuadRenderer2D      renderer;
    AtlasImporter       atlas;

    void    BuildQuads();

};

typedef SmartPtr<SpriteMap>     SpriteMapPtr;
//typedef SpriteMap*     SpriteMapPtr;

#endif // SPRITEMAP_H
