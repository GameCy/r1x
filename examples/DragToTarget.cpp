#include "DragToTarget.h"
#include "Graphics.h"
#include <math.h>


QVector2D toPixels(float sx, float sy, bool useAspectRatio)
{
    float W = Graphics::Screen.Width();
    float H = Graphics::Screen.Height();

    W = sx*W;
    if (useAspectRatio)     H = sy*H* Graphics::DPI.ASPECT_RATIO;
    else                    H = sy*H;
    return QVector2D(W,H);
}

bool isInsideBox(QVector2D pos, QVector2D bottomLeft, QVector2D siz)
{
    auto topRight = bottomLeft + siz;
    return pos.x()>bottomLeft.x() &&
           pos.x()<topRight.x() &&
           pos.y()>bottomLeft.y() &&
           pos.y()<topRight.y();
}

Circle::Circle(DropTargetList *targetList, SpriteMap &atlas)
    : sprite( atlas.CreateSprite("slot.png") )
{
    SetTargetList(targetList);
    // Add draggables to manager
    DragDropManager::Instance()->Draggables.push_back(this);
}

Circle::~Circle()
{
    DragDropManager::Instance()->Draggables.remove(this);
}

bool Circle::IsInside(QVector2D pos)
{
    return isInsideBox(pos, sprite->getPos(), sprite->getSize());
}

void Circle::OnStateChanged(DragStates newState)
{
//    if (newState==Release)
}

void Circle::Update()
{
    if (IsDragging())
    {
        sprite->setPos(GetLastPosition() - sprite->getSize()/2.f );
    }
}

void Circle::ResetLocation()
{
    this->
    sprite->setPos( toPixels(0.4f, 0.3f, true));
}

// ---------------------------------------------------------------

TargetBox::TargetBox(QVector2D pos, SpriteMap &atlas)
    : sprite( atlas.CreateSprite("Label.png"))
{
    sprite->setPos( QVector2D(pos) );
}

bool TargetBox::IsInside(QVector2D pos, Draggable *source)
{
    if (isInsideBox(pos, sprite->getPos(), sprite->getSize()))
    {
        Circle* c = (Circle*) source;
        if (c)
            c->ResetLocation();
        return true;
    }
    return false;
}

// ---------------------------------------------------------------

DragToTarget::DragToTarget()
    : atlas(50, ":/textures/textures.atlas")
    , targetBox(nullptr)
{
    //Create Dragables
    circle = new Circle( &targets, atlas );

    // Create targetList with DropTargets
    targetBox = new TargetBox( toPixels(0.4f, 0.9f, true), atlas);
    targets.Add(targetBox);

    Resize( Graphics::Screen );
    Begin();
}

DragToTarget::~DragToTarget()
{
    delete circle;
    delete targetBox;
    //DragDropManager::DestroyInstance();
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
    Graphics::rasterShader->UpdateViewport( screen );

    circle->ResetLocation();
    circle->sprite->setSize( toPixels(0.2f, 0.2f, true) );
    targetBox->sprite->setPos( toPixels(0.3f, 0.9f, true));
    targetBox->sprite->setSize( toPixels(0.4f, 0.3f, true) );
}
