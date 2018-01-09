#ifndef _ENTITY_HEADER_
#define _ENTITY_HEADER_
#include <QVector3D>
#include <QQuaternion>
#include "SmartPtr.h"
#include "Camera.h"
#include "Model.h"

class Entity : virtual public RefCountBase
{
public:
    virtual void	Render(CameraPtr camera)=0;
    virtual void	Update(float dt)=0;
    virtual bool	IsFinished()=0;

    virtual QVector3D	GetPos();
    virtual void	SetPos(QVector3D pos);
    virtual QQuaternion	GetRotation();
    virtual void	SetRotation(QQuaternion rot);

    ModelPtr getModel() const;
    void setModel(const ModelPtr &value);

protected:
    Entity() {}

    QVector3D   pos;
    QQuaternion rot;

    ModelPtr    model;
};

typedef SmartPtr<Entity>	EntityPtr;
//typedef Entity*	EntityPtr;

#endif
