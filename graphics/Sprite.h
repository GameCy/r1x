#ifndef _SPRITE_H
#define _SPRITE_H
#include <QVector2D>
#include <vector>
#include "Material.h"
#include "QuadRenderers.h"
#include "AtlasImporter.h"

class Sprite
{
public:
    Sprite(UVRect _uvRect);

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

class Sprite2 : public Sprite
{
public:
    Sprite2(UVRect _uvRect);

    QColor Color;

};

#endif // _SPRITE_H
