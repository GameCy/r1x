#ifndef _ENTITY_MANAGER_HEADER_
#define _ENTITY_MANAGER_HEADER_
#include "Entity.h"
#include "SmartPtr.h"
#include <list>
#include "IClipper.h"
#include <QOpenGLTexture>
#include <QVector3D>
#include <QQuaternion>
#include "Camera.h"

typedef std::list<EntityPtr>	EntityList;

class EntityManager
{
public:
	static EntityManager&	Instance();
	static void				DestroyInstance();

	virtual ~EntityManager();

	void Add(EntityPtr obj);
	void AddEffect(EntityPtr obj);

	void Update(float dt);
	void ForceKillAll();
	void Render();

	void SetClipper(IClipper* areaClipper);

    void resizeDisplay(int width, int height);
    bool InitShaders();

    Camera camera;

private:
	EntityList	Entities;
	EntityList	Effects;
	IClipper*	AreaClipper;

	EntityManager();
	static EntityManager*	instance;

	void UpdateInternal(EntityList &entities, float dt);
	void RenderInternal(EntityList &entities);
    void updateCamera(QVector3D objectPos, QQuaternion objectRotation);
};

#endif
