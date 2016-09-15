#ifndef _ENTITY_HEADER_
#define _ENTITY_HEADER_
#include "SmartPtr.h"
#include <QVector3D>
#include <QQuaternion>
#include "Camera.h"

class Entity : public RefCountBase
{
public:
	virtual ~Entity() 	{}

    virtual void	Render(Camera &camera)=0;
	virtual void	Update(float dt)=0;
	virtual bool	IsFinished()=0;

    virtual QVector3D GetPos();
    virtual void	 SetPos(QVector3D pos);
    virtual QQuaternion GetRotation();
    virtual void	 SetRotation(QQuaternion rot);

protected:
    Entity() {}

    QVector3D pos;
    QQuaternion rot;
};

typedef SmartPtr<Entity>	EntityPtr;

#endif
