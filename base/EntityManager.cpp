#include "EntityManager.h"
#include "QuadRenderer.h"

EntityManager*	EntityManager::instance=0; // 

EntityManager& EntityManager::Instance()
{
    if (instance==0)    { instance = new EntityManager();  }
	return (*instance);
}

void EntityManager::DestroyInstance()
{
    if (instance)	{ delete instance; instance=0; }
}

EntityManager::EntityManager()	: AreaClipper(0)	{ }

EntityManager::~EntityManager()
{
	ForceKillAll(); 
}

bool EntityManager::InitShaders()
{
    return camera.InitShaders();
}

void EntityManager::Add(EntityPtr obj)			{ Entities.push_back(obj); }

void EntityManager::AddEffect(EntityPtr obj)	{ Effects.push_back(obj); }

void EntityManager::SetClipper(IClipper* areaClipper)	{ AreaClipper = areaClipper; }

void EntityManager::ForceKillAll()				
{
	Entities.clear(); 
	Effects.clear();
}

void EntityManager::Update(float dt)
{
	UpdateInternal(Entities, dt);
    camera.UpdateViewVectors();
    UpdateInternal(Effects, dt);
}

void EntityManager::Render()
{
    camera.ParticleRenderingMode(false);
	RenderInternal(Entities);

    camera.ParticleRenderingMode(true);
    RenderInternal(Effects);
}

void EntityManager::UpdateInternal(EntityList &entities, float dt)
{
	EntityList::iterator p;
	for(p= entities.begin(); p!=entities.end(); )
	{
		EntityPtr obj = *p;
		obj->Update( dt);
		
		if (obj->IsFinished())
			p = entities.erase(p);
		else
			++p;
	}
}

void EntityManager::RenderInternal(EntityList &entities)
{
	EntityList::iterator p;
	for(p= entities.begin(); p!=entities.end(); ++p)
	{
        QVector3D pos = (*p)->GetPos();
        if (!AreaClipper || AreaClipper->InVisibleArea(pos) )
        {
            (*p)->Render(camera);
        }
	}
}

//-----------

void EntityManager::resizeDisplay(int width, int height)
{
    camera.Setup(width, height, 1.0f, 1100.0f, 60.0f, float(width)/float(height));
}
