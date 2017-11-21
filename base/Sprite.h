#ifndef _SPRITE_H
#define _SPRITE_H
#include "Entity.h"
#include <QVector2D>
#include <vector>
#include "Material.h"
#include "QuadRenderer2D.h"
#include "AtlasImporter.h"

class Sprite
{
public:
    Sprite(float width, float height, UVRect _uvRect);

    void    SetVisible(bool visible);
    bool    IsVisible();

    QVector2D getPos() const;
    void setPos(const QVector2D &value);

    QVector2D getSize() const;
    void setSize(const QVector2D &value);

    UVRect &getUVRect();
    void setUVRect(const UVRect &value);

    void ClearChangedFlag();

    friend class SpriteMap;
private:
    QVector2D   Pos;
    QVector2D   Size;
    UVRect      uvRect;
    bool        isVisible;
    bool        hasChanged;
};

#endif // _SPRITE_H
