#include "SpriteMap.h"
#include "Utils.h"

SpriteMap::SpriteMap(int maxQuads, QString path, bool useColorPerSprite)
    : renderer(nullptr)
    , colorPerSprite(useColorPerSprite)
    , rebuiltQuads(false)
{
    MaterialPtr mat = LoadMaterial(path);

    if (useColorPerSprite)  renderer = new QuadRenderer2DX(maxQuads, mat );
    else                    renderer = new QuadRenderer2D(maxQuads, mat );
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

MaterialPtr SpriteMap::LoadMaterial(QString path)
{
    if (!atlas.Load(path, true))
        return new Material(path); // load as simple texture

    return new Material( Utils::getFolder(path) + "/" + atlas.TexFileName );
}

Sprite* SpriteMap::CreateSprite(QString spriteName)
{
    UVRect uvRect(0,0,1,1);
    if (spriteName.isEmpty()==false && atlas.IsValid())
    {
        if (!atlas.GetUVRect(spriteName, uvRect))
            return 0;
    }
    Sprite* sprite = new Sprite(uvRect);
    sprites.push_back(sprite);
    rebuiltQuads=true;
    return sprite;
}

Sprite *SpriteMap::CreateClone(Sprite *other)
{
    Sprite* sprite = new Sprite();
    sprite->CloneFrom(other);
    sprites.push_back(sprite);
    rebuiltQuads=true;
    return sprite;
}

bool SpriteMap::DestroySprite(Sprite *sprite)
{
    int removed = sprites.removeAll(sprite);
    delete sprite;
    rebuiltQuads=true;
    return (removed>0);
}

void SpriteMap::DestroyAllSprites()
{
    sprites.clear();
    rebuiltQuads=true;
}

bool SpriteMap::GetUVRect(QString spriteName, UVRect &uvRect)
{
    return atlas.GetUVRect(spriteName, uvRect);
}

AtlasImporter &SpriteMap::GetAtlas()
{
    return atlas;
}

void SpriteMap::SetQuad2D(Sprite* spr, int quadIndex)
{
    Quad2D &quad = ((QuadRenderer2D*)renderer)->getQuad(quadIndex);
    quad.SetUVRect( spr->getUVRect() );
    if (fabsf(spr->RotationAngle)<0.0005f)
    {
        auto p = spr->Pos - spr->RotationCenter;
        quad.SetGeometry(p.x(), p.y(), spr->Size.x(), spr->Size.y());
    }
    else
    {
        RotateAndSetGeometry<Quad2D>( quad, spr->Pos
                                     , spr->Size
                                     , spr->RotationCenter
                                     , spr->RotationAngle);
    }
}

void SpriteMap::SetQuad2DX(Sprite* spr, int quadIndex)
{
    Quad2DX &quad = ((QuadRenderer2DX*)renderer)->getQuad(quadIndex);
    quad.SetUVRect( spr->uvRect );
    quad.SetAllColors( spr->Color );
    if (fabsf(spr->RotationAngle)<0.0005f)
    {
        auto p = spr->Pos - spr->RotationCenter;
        quad.SetGeometry(p.x(), p.y(), spr->Size.x(), spr->Size.y());
    }
    else
    {
        RotateAndSetGeometry<Quad2DX>( quad, spr->Pos
                                     , spr->Size
                                     , spr->RotationCenter
                                     , spr->RotationAngle);
    }
}

void SpriteMap::BuildQuads()
{
    rebuiltQuads = false;
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
    QVector<Sprite*>::iterator spr = sprites.begin();
    while(spr!=sprites.end())
    {
        Sprite* sprite = (*spr);
        if (sprite->deleteLater)
        {
            delete sprite;
            spr = sprites.erase(spr);
            rebuiltQuads=true;
        }
        else
            spr++;
    }

    if (!rebuiltQuads)
    {
        for(int i=0; i<sprites.size(); ++i)
        {
            if (sprites[i]->hasChanged || sprites[i]->deleteLater)
            {
                rebuiltQuads=true;
                break;
            }
        }
    }
    if(rebuiltQuads)
        BuildQuads();
}
