#pragma once
#include "TextureAnim.h"
#include "Entity.h"
#include "QuadRenderer.h"
#include <vector>


class SmokeTrail;
typedef SmartPtr<SmokeTrail>	SmokeTrailPtr;

class SmokeTrail : public Entity
{
public:
    SmokeTrail(int numParticles, TextureAnimPtr texAnim
              , float duration=0.7, float radius=2.0, float bilboardSize=1.0);
    virtual ~SmokeTrail(void);

	// Entity implementation
	virtual void Update(float dt);
	virtual bool IsFinished();
    virtual void Render(Camera &camera);
    virtual QVector3D	GetPos();

    void    setTrackedTarget(EntityPtr target);
    void    trackTargetAddParticle();
    void    TerminateTrail();

private:
    void    UpdateQuadsFromParticles(QVector3D screenRight, QVector3D screenUp);

    QuadRenderer   renderer;
    bool    finished;

    float	bilboardSize;
    float	emitDt;
    float	duration;
	float	radius;

    std::vector<Particle> Particles;
    int     numParticles;
    QVector3D   lastPos;

	TextureAnimPtr	textureAnim;

    EntityPtr   trackedTarget;
};
