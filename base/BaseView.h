#ifndef BASEVIEW_H
#define BASEVIEW_H
#include "SmartPtr.h"
#include "EntityCollection.h"
#include "Camera.h"

class BaseView : public EntityCollection, public RefCountBase
{
public:
    BaseView();

    virtual void Render();
    virtual void Update(float dt);
    virtual void Resize(float width, float height);

    CameraPtr getCamera() const;
    void setCamera(const CameraPtr &value);

private:
    CameraPtr camPtr;
};

typedef SmartPtr<BaseView>  BaseViewPtr;
//typedef BaseView*  BaseViewPtr;

#endif // BASEVIEW_H
