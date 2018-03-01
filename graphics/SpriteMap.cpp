#include "SpriteMap.h"
#include "Utils.h"

SpriteMap::SpriteMap(int maxQuads, QString atlasPath)
    : atlas(atlasPath, true)
{
    QString texturePath = Utils::getFolder(atlasPath) + "/" + atlas.TexFileName;
    renderer = new QuadRenderer2D(maxQuads, new Material(texturePath) );
}

SpriteMap::~SpriteMap()
{
    foreach (auto sprite, sprites)
    {
        delete sprite;
    }
    if (renderer)
        delete renderer;
}

MaterialPtr SpriteMap::GetMaterial()
{
    return renderer->GetMaterial();
}

Sprite* SpriteMap::CreateSprite(QString spriteName)
{
    UVRect uvRect;
    if (!atlas.GetUVRect(spriteName, uvRect))
        return 0;
    Sprite* sprite = new Sprite(uvRect);
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
    renderer->ReserveActiveQuads( CountVisibleSprites() );

    int numSprites = sprites.size();
    int quadCount=0;
    for(int i=0; i<numSprites; ++i)
    {
        Sprite* spr = sprites[i];
        if (!spr->IsVisible())
            continue;

        Quad2D &quad = ((QuadRenderer2D*)renderer)->getQuad(quadCount);
        quadCount++;

        quad.SetGeometry(spr->Pos.x(), spr->Pos.y(), spr->Size.x(), spr->Size.y());
        quad.SetUVRect( spr->getUVRect() );
        spr->ClearChangedFlag();
    }
    renderer->UpdateQuadsBuffer();
}

int SpriteMap::CountVisibleSprites()
{
    int numSprites = sprites.size();
    int visibleSprites = 0;
    for(int i=0; i<numSprites; ++i)
    {
        if (sprites[i]->IsVisible())
            visibleSprites++;
    }
    return visibleSprites;
}

void SpriteMap::Render()
{
    renderer->RenderQuads();
}

void SpriteMap::Update()
{
    for(int i=0; i<sprites.size(); ++i)
    {
        if (sprites[i]->hasChanged)
        {
            BuildQuads();
            break;
        }
    }
}

