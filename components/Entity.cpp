#include "Entity.h"

//Entity::Entity()
//{
//}
//
//Entity::~Entity()
//{
//}

QVector3D	Entity::GetPos()
{
	return pos;
}

void	Entity::SetPos(QVector3D pos)
{
	this->pos = pos;
}

QQuaternion Entity::GetRotation()
{
    return rot;
}

void	 Entity::SetRotation(QQuaternion rot)
{
    this->rot = rot;
}

ModelPtr Entity::getModel() const
{
    return model;
}

void Entity::setModel(const ModelPtr &value)
{
    model = value;
}

