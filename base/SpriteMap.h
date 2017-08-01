#ifndef SPRITEMAP_H
#define SPRITEMAP_H
#include "Entity.h"
#include "Sprite.h"
#include "AtlasImporter.h"
#include <QVector2D>
#include <vector>
#include "Material.h"
#include "QuadRenderer2D.h"


class SpriteMap : public Entity
{
public:
    SpriteMap(int maxQuads, QString atlasPath);

    SpritePtr   CreateSprite(QString spriteName, float width, float height);
    MaterialPtr GetMaterial();
    bool GetUVRect(QString spriteName, UVRect &uvRect);

private:
    QVector<SpritePtr>  sprites;
    QuadRenderer2D      renderer;
    AtlasImporter       atlas;

    void    BuildQuads();
public: // Entity interface
    void Render(CameraPtr camera);
    void Update(float dt);
    bool IsFinished();
};

typedef SmartPtr<SpriteMap>     SpriteMapPtr;
//typedef SpriteMap*     SpriteMapPtr;

#endif // SPRITEMAP_H
