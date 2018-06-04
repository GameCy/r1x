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
    inline bool    IsVisible()    { return isVisible; }

    inline QVector2D getPos() const    { return Pos; }
    inline void setPos(const QVector2D &value)
    {
        Pos = value;
        hasChanged = true;
    }

    inline QVector2D getSize() const    { return Size; }
    inline void setSize(const QVector2D &value)
    {
        Size = value;
        hasChanged = true;
    }

    inline QColor getColor() const    { return Color; }
    inline void setColor(const QColor &value)
    {
        Color = value;
        hasChanged = true;
    }

    inline UVRect &getUVRect()    { return uvRect; }
    inline void setUVRect(const UVRect &value)
    {
        uvRect = value;
        hasChanged = true;
    }

    inline void DeleteLater()
    {
        deleteLater=true;
    }

    inline void ClearChangedFlag()    { hasChanged = false; }

    Sprite *CloneFrom(Sprite* other);

    void Animate(float duration, UVRectArray *frames);
    inline SpriteAnimator* GetAnimator()    { return animator;}

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
