#pragma once
#include "TextureAnim.h"
#include "Entity.h"
#include "QuadRenderer.h"
#include <list>

class FakeShadows;
typedef SmartPtr<FakeShadows>	FakeShadowsPtr;

class FakeShadows : public Entity
{
public:
    FakeShadows(int numParticles, TextureAnimPtr texAnim, float shadowSize=1.0);
    virtual ~FakeShadows(void);

    void    AddShadowCaster(EntityPtr entity);
    void    RemoveShadowCaster(EntityPtr entity);

	// Entity implementation
	virtual void Update(float dt);
    virtual void Render(Camera &camera);
    virtual bool IsFinished();


private:
    QuadRenderer   renderer;

    std::list<EntityPtr>    shadowCasters;

    float	shadowSize;

	TextureAnimPtr	textureAnim;

    void    UpdateShadowQuads();
};
