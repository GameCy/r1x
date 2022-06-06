#ifndef DRAGTOTARGET_H
#define DRAGTOTARGET_H
#include "ExampleBase.h"
#include "SpriteMap.h"
#include "DragDrop.h"

QVector2D toPixels(float sx, float sy, bool useAspectRatio);

class Circle : public Draggable
{
public:
    Circle(DropTargetList* targetList, SpriteMap& atlas);
    virtual ~Circle();

    void Update();
    void ResetLocation();

    Sprite* sprite;

    // Draggable interface
    virtual bool IsInside(QVector2D pos);
    void OnStateChanged(DragStates newState);
};

// ---------------------------------------------------------------

class TargetBox : public DropTarget
{
public:
    TargetBox(QVector2D pos, SpriteMap& atlas);
    virtual ~TargetBox() {}
    virtual bool IsInside(QVector2D pos, Draggable* source);

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
};

#endif // DRAGTOTARGET_H
