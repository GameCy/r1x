#pragma once
#include "TextureAnim.h"
#include "Entity.h"
#include "QuadRenderer.h"


class Explosion;
typedef SmartPtr<Explosion>	ExplosionPtr;

class Explosion : public Entity
{
public:
	// this is like a factory (can be extracted later)
	static ExplosionPtr	CreateExplosion();
	static ExplosionPtr	CreateExplosion2();
	static ExplosionPtr	CreatePuff();
    static ExplosionPtr	CreateFlash();

    Explosion(int numParticles, TextureAnimPtr texAnim
              , float duration=0.7, float radius=2.0, float bilboardSize=1.0);
	virtual ~Explosion(void);

	// Entity implementation
	virtual void Update(float dt);
	virtual bool IsFinished();
    virtual void Render(Camera &camera);
    virtual QVector3D	GetPos();

	void	Restart();

private:
	void	ResetParticle(Particle* p);
    void    UpdateQuadsFromParticles(QVector3D screenRight, QVector3D screenUp);

    QuadRenderer   renderer;

	float	bilboardSize;
	float	m_t;
	float	duration;
	float	radius;

    std::vector<Particle> Particles;
	
	TextureAnimPtr	textureAnim;

};
