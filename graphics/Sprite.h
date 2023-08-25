#ifndef _SPRITE_H
#define _SPRITE_H
#include <QVector2D>
#include <QColor>
#include <QRectF>
#include "UVRectArray.h"

class Sprite
{
public:
    Sprite();
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

    inline void CenterAt(const QVector2D &center)
    {
        Pos = center - Size/2.f;
        hasChanged = true;
    }

    inline float getRotationAngle() const    { return RotationAngle; }
    inline void setRotationAngle(float value)
    {
        RotationAngle = value;
        hasChanged = true;
    }

    inline QVector2D getRotationCenter() const    { return RotationCenter; }
    inline void setRotationCenter(const QVector2D &value)
    {
        RotationCenter = value;
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

    QRectF  calcRect();

    inline void DeleteLater()
    {
        deleteLater=true;
    }

    inline void ClearChangedFlag()    { hasChanged = false; }
    inline bool wasChanged() { return hasChanged; }

    void CloneFrom(Sprite* other);

    friend class SpriteMap;
private:
    QVector2D   Pos;
    float       RotationAngle;
    QVector2D   RotationCenter;
    QVector2D   Size;
    QColor      Color;
    UVRect      uvRect;
    bool        isVisible;
    bool        hasChanged;
    bool        deleteLater;
};

#endif // _SPRITE_H
