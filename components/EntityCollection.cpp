#include "EntityCollection.h"

void EntityCollection::Update(float dt)
{
    EntityList::iterator p;
    for(p=begin(); p!=end(); )
    {
        EntityPtr obj = *p;

        if (obj->IsFinished())
        {
            p = erase(p);
        }
        else
        {
            obj->Update( dt);
            ++p;
        }
    }
}

void EntityCollection::Render(CameraPtr camera, IClipper *areaClipper)
{
    EntityList::iterator p;
    for(p=begin(); p!=end(); ++p)
    {
        QVector3D pos = (*p)->GetPos();
        if (!areaClipper || areaClipper->InVisibleArea(pos) )
        {
            (*p)->Render(camera);
        }
    }
}
