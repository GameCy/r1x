#include "BaseView.h"

BaseView::BaseView()
{
}

void BaseView::Render()
{
    EntityCollection::Render(getCamera(),0);
}

void BaseView::Update(float dt)
{
    EntityCollection::Update(dt);
}


void BaseView::Resize(float width, float height)
{
    getCamera()->Setup(width, height, 1.0f, 1100.0f, 60.0f, float(width)/float(height));
}

CameraPtr BaseView::getCamera() const
{
    return camPtr;
}

void BaseView::setCamera(const CameraPtr &value)
{
    camPtr = value;
}

