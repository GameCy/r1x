#include "base/SpriteMap.h"
#include "Utils.h"

SpriteMap::SpriteMap(int maxQuads, QString atlasPath)
    : atlas(atlasPath, true)
{
    QString texturePath = Utils::getFolder(atlasPath) + "/" + atlas.TexFileName;
    renderer.Init(maxQuads, texturePath);
}

MaterialPtr SpriteMap::GetMaterial()
{
    return renderer.GetMaterial();
}

SpritePtr SpriteMap::CreateSprite(QString spriteName, float width, float height)
{
    UVRect uvRect;
    if (!atlas.GetUVRect(spriteName, uvRect))
        return 0;
    Sprite* sprite = new Sprite(width, height, uvRect);
    sprites.push_back(sprite);
    return sprite;
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
        SpritePtr spr = sprites[i];
        if (!spr->IsVisible())
            continue;
        Quad2D &quad = renderer.getQuad(quadCount);
        quadCount++;

        quad.SetGeometry(spr->Pos.x(), spr->Pos.y(), spr->Size.x(), spr->Size.y());
        quad.SetUVs(spr->UVstart.x(), spr->UVstart.y(), spr->UVsize.x(), spr->UVsize.y());
        spr->ClearChangedFlag();
    }
    renderer.UpdateQuadsBuffer();
}

void SpriteMap::Render(CameraPtr camera)
{
    renderer.RenderQuads();
}

void SpriteMap::Update(float dt)
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

bool SpriteMap::IsFinished()    { return false; }


