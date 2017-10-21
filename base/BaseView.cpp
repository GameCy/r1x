#include "BaseView.h"

BaseView::BaseView(CameraPtr cam)
    : camera(cam)
{
}

void BaseView::Render()
{
    EntityCollection::Render(camera, 0);
}

void BaseView::Update(float dt)
{
    EntityCollection::Update(dt);
}


void BaseView::Resize(float width, float height)
{
}

