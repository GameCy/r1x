#ifndef ENTITYCOLLECTION_H
#define ENTITYCOLLECTION_H
#include "Entity.h"
#include <QList>

typedef QList<EntityPtr>   EntityList;

class EntityCollection : public EntityList
{
public:
    void Update(float dt);
    void Render(CameraPtr camera, IClipper*	areaClipper);
};


#endif // ENTITYCOLLECTION_H
