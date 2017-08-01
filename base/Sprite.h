#ifndef _SPRITE_H
#define _SPRITE_H
#include "Entity.h"
#include <QVector2D>
#include <vector>
#include "Material.h"
#include "QuadRenderer2D.h"
#include "AtlasImporter.h"

class Sprite// : public RefCountBase
{
public:
    Sprite(float width, float height, float u1, float v1, float u2, float v2);
    Sprite(float width, float height, UVRect uvs);

    void    SetVisible(bool visible);
    bool    IsVisible();

    QVector2D getPos() const;
    void setPos(const QVector2D &value);

    QVector2D getSize() const;
    void setSize(const QVector2D &value);

    QVector2D getUVstart() const;
    void setUVstart(const QVector2D &value);

    QVector2D getUVsize() const;
    void setUVsize(const QVector2D &value);

    void ClearChangedFlag();

    friend class SpriteMap;
private:
    QVector2D   Pos;
    QVector2D   Size;
    QVector2D   UVstart;
    QVector2D   UVsize;
    bool        isVisible;
    bool        hasChanged;
};

//typedef SmartPtr<Sprite>    SpritePtr;
typedef Sprite*    SpritePtr;

#endif // _SPRITE_H
