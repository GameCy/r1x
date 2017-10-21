#ifndef BASEVIEW_H
#define BASEVIEW_H
#include "SmartPtr.h"
#include "EntityCollection.h"
#include "Camera.h"
#include "ViewPort.h"

class BaseView : public EntityCollection, public RefCountBase
{
public:
    BaseView(CameraPtr cam);

    virtual void Render();
    virtual void Update(float dt);
    virtual void Resize(float width, float height);

private:
    CameraPtr camera;
};

typedef SmartPtr<BaseView>  BaseViewPtr;
//typedef BaseView*  BaseViewPtr;

#endif // BASEVIEW_H
