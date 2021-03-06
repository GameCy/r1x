#include "DragToTarget.h"
#include "Graphics.h"
#include <math.h>


bool isInsideBox(QVector2D pos, QVector2D bottomLeft, QVector2D siz)
{
    auto topRight = bottomLeft + siz;
    return pos.x()>bottomLeft.x() &&
           pos.x()<topRight.x() &&
           pos.y()>bottomLeft.y() &&
           pos.y()<topRight.y();
}

Circle::Circle(QPoint pos, DropTargetList *targetList, SpriteMap &atlas)
    : sprite( atlas.CreateSprite("slot.png") )
    , initialPos(pos)
{
    EndDrag(pos);
    sprite->setPos(QVector2D(pos));
    SetTargetList(targetList);
}

bool Circle::IsInside(QPoint pos)
{
    QVector2D p(pos);
    if(isInsideBox(p, sprite->getPos(), sprite->getSize()))
    {
        distanceFromHold = p - sprite->getPos();
        return true;
    }
    return false;
}

void Circle::Update()
{
//    if (IsDragging())
    {
        sprite->setPos(QVector2D( GetLastPosition()) - distanceFromHold);
    }
}

void Circle::ResetPos()
{
    distanceFromHold = QVector2D(0,0);
    EndDrag(initialPos.toPoint());
}

// ---------------------------------------------------------------

TargetBox::TargetBox(QPoint pos, SpriteMap &atlas)
    :sprite( atlas.CreateSprite("Label.png"))
{
    sprite->setPos( QVector2D(pos) );
}

bool TargetBox::IsDropedInside(QPoint pos, Draggable *source)
{
    QVector2D p(pos);
    if(isInsideBox(p, sprite->getPos(), sprite->getSize()))
    {
        ((Circle*)source)->ResetPos();
        return true;
    }
    return false;
}

// ---------------------------------------------------------------

DragToTarget::DragToTarget()
    : atlas(50, ":/textures/textures.atlas")
{
    screenWidth = Graphics::Screen.Width();
    screenHeight= Graphics::Screen.Height();

    gDragDropManager = new DragDropManager();

    //Create Dragables
    circle = new Circle( toPixels(0.2f,0.5f), &targets, atlas );

    // Create targetList with DropTargets
    targetBox = new TargetBox( toPixels(0.2f,0.8f), atlas);
    targets.Add(targetBox);

    // Add draggables to manager
    gDragDropManager->Draggables.push_back(circle);

    Resize( Graphics::Screen );
    Begin();
}

DragToTarget::~DragToTarget()
{
    delete gDragDropManager;
    gDragDropManager=nullptr;
    delete circle;
    delete targetBox;
}

void DragToTarget::Render()
{
    if (!Graphics::rasterShader->Bind())
        return;

    atlas.Render();
}

void DragToTarget::Update(float dt)
{
    circle->Update();
    atlas.Update();
}

void DragToTarget::Resize(ViewPort &screen)
{
    screenWidth = screen.Width();
    screenHeight = screen.Height();
    Graphics::rasterShader->UpdateViewport( screen );

    circle->sprite->setSize( QVector2D(toPixels(0.2f, 0.2f, true)) );
    targetBox->sprite->setSize( QVector2D(toPixels(0.4f, 0.3f, true)) );
}

QPoint DragToTarget::toPixels(float sx, float sy, bool useAspectRatio)
{
    float W = sx*screenWidth;
    float H;
    if (useAspectRatio)     H = sy*screenHeight * Graphics::DPI.ASPECT_RATIO;
    else                    H = sy*screenHeight;
    return QPoint(W,H);
}
