#include "SpriteMap.h"
#include "Utils.h"

SpriteMap::SpriteMap(int maxQuads, QString atlasPath)
    : atlas(atlasPath, true)
{
    QString texturePath = Utils::getFolder(atlasPath) + "/" + atlas.TexFileName;
    renderer.Init(maxQuads, texturePath);
}

SpriteMap::~SpriteMap()
{
    foreach (auto sprite, sprites)
    {
        delete sprite;
    }
}

MaterialPtr SpriteMap::GetMaterial()
{
    return renderer.GetMaterial();
}

Sprite* SpriteMap::CreateSprite(QString spriteName, float width, float height)
{
    UVRect uvRect;
    if (!atlas.GetUVRect(spriteName, uvRect))
        return 0;
    Sprite* sprite = new Sprite(width, height, uvRect);
    sprites.push_back(sprite);
    return sprite;
}

bool SpriteMap::DestroySprite(Sprite *sprite)
{
    int removed = sprites.removeAll(sprite);
    delete sprite;
    return (removed>0);
}

bool SpriteMap::GetUVRect(QString spriteName, UVRect &uvRect)
{
    return atlas.GetUVRect(spriteName, uvRect);
}

void SpriteMap::BuildQuads()
{
    int numSprites = sprites.size();
    int visibleSprites = 0;
    for(int i=0; i<numSprites; ++i)
    {
        if (sprites[i]->IsVisible())
            visibleSprites++;
    }
    renderer.ReserveActiveQuads(visibleSprites);
    int quadCount=0;
    for(int i=0; i<numSprites; ++i)
    {
        Sprite* spr = sprites[i];
        if (!spr->IsVisible())
            continue;
        Quad2D &quad = renderer.getQuad(quadCount);
        quadCount++;

        quad.SetGeometry(spr->Pos.x(), spr->Pos.y(), spr->Size.x(), spr->Size.y());
        quad.SetUVRect( spr->getUVRect() );
        spr->ClearChangedFlag();
    }
    renderer.UpdateQuadsBuffer();
}

void SpriteMap::Render()
{
    renderer.RenderQuads();
}

void SpriteMap::Update()
{
    for(int i=0; i<sprites.size(); ++i)
    {
        if (sprites[i]->hasChanged)
        {
            BuildQuads(); // build for all quads and exit loop
            break;
        }
    }
}

