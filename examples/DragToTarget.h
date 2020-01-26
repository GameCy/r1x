#ifndef DRAGTOTARGET_H
#define DRAGTOTARGET_H
#include "ExampleBase.h"
#include "SpriteMap.h"
#include "DragDrop.h"


class Circle : public Draggable
{
public:
    Circle(QPoint pos, DropTargetList* targetList, SpriteMap& atlas);
    virtual ~Circle() {}
    virtual bool IsInside(QPoint pos);
    void Update();

    Sprite* sprite;
    QVector2D   distanceFromHold;
};

// ---------------------------------------------------------------

class TargetBox : public DropTarget
{
public:
    TargetBox(QPoint pos, SpriteMap& atlas);
    virtual ~TargetBox() {}
    virtual bool IsInside(QPoint pos, Draggable* source);

    Sprite* sprite;
};

// ---------------------------------------------------------------

class DragToTarget : public ExampleBase
{
public:
    DragToTarget();
    virtual ~DragToTarget();

    // Temporal interface
    void Update(float dt);
    // ExampleBase interface
    void Render();
    void Resize(ViewPort &screen);

private:
    SpriteMap   atlas;
    Circle*     circle;
    TargetBox*  targetBox;
    DropTargetList targets;

    QPoint      toPixels(float sx, float sy, bool useAspectRatio=false);
    float       screenWidth;
    float       screenHeight;
};

#endif // DRAGTOTARGET_H
