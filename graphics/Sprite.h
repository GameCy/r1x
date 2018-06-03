#ifndef _SPRITE_H
#define _SPRITE_H
#include <QVector2D>
#include <QColor>
#include "UVRectArray.h"

class SpriteAnimator;

class Sprite
{
public:
    Sprite(UVRect _uvRect);
    ~Sprite();

    void    SetVisible(bool visible);
    bool    IsVisible();

    QVector2D getPos() const;
    void setPos(const QVector2D &value);

    QVector2D getSize() const;
    void setSize(const QVector2D &value);

    QColor getColor() const;
    void setColor(const QColor &value);

    UVRect &getUVRect();
    void setUVRect(const UVRect &value);

    void DeleteLater();

    Sprite *CloneFrom(Sprite* other);

    void ClearChangedFlag();

    void Animate(float duration, UVRectArray *frames);

    friend class SpriteMap;
private:
    QVector2D   Pos;
    QVector2D   Size;
    QColor      Color;
    UVRect      uvRect;
    bool        isVisible;
    bool        hasChanged;
    bool        deleteLater;

    SpriteAnimator *animator;
};

#endif // _SPRITE_H
