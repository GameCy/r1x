#include "SpriteMap.h"
#include "Utils.h"

SpriteMap::SpriteMap(int maxQuads, QString atlasPath, bool useColorPerSprite)
    : atlas(atlasPath, true)
    , colorPerSprite(useColorPerSprite)
{
    QString texturePath = Utils::getFolder(atlasPath) + "/" + atlas.TexFileName;
    MaterialPtr mat = new Material(texturePath);
    if (useColorPerSprite)
        renderer = new QuadRenderer2DX(maxQuads, mat );
    else
        renderer = new QuadRenderer2D(maxQuads, mat );
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

void SpriteMap::SetQuad2D(Sprite* spr, int quadIndex)
{
    Quad2D &quad = ((QuadRenderer2D*)renderer)->getQuad(quadIndex);
    quad.SetGeometry(spr->Pos.x(), spr->Pos.y(), spr->Size.x(), spr->Size.y());
    quad.SetUVRect( spr->getUVRect() );
}

void SpriteMap::SetQuad2DX(Sprite* spr, int quadIndex)
{
    Quad2DX &quad = ((QuadRenderer2DX*)renderer)->getQuad(quadIndex);
    quad.SetGeometry(spr->Pos.x(), spr->Pos.y(), spr->Size.x(), spr->Size.y());
    quad.SetUVRect( spr->uvRect );
    quad.SetAllColors( spr->Color );
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

        if (colorPerSprite) SetQuad2DX(spr, quadCount);
        else                SetQuad2D(spr, quadCount);

        spr->ClearChangedFlag();

        quadCount++;
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

