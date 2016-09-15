#include "Explosion.h"
#include <math.h>


char cExplosion[] = ":/textures/explosion.png";
char cExplosion2[] = ":/textures/explosion2.png";
char cFireAura[] = ":/textures/FireyAura.png";
char cSmoke1[] = "smoke1";
char cFlash1[] = ":/textures/flash1.png";

ExplosionPtr	Explosion::CreateExplosion()
{
    return new Explosion(4, TextureAnim::Create( cExplosion, 0.7f, 5, 5, 25), 0.7f, 0.9f, 0.8f );
}

ExplosionPtr	Explosion::CreateExplosion2()
{
    return new Explosion(12, TextureAnim::Create( cExplosion2, 0.7f, 2, 2, 4), 0.6f, 0.5f );
}

ExplosionPtr	Explosion::CreatePuff()
{
    return new Explosion(1, TextureAnim::Create( cFireAura, 1.5f, 3, 7, 21), 0.9, 0.0, 1.5 );
}

ExplosionPtr	Explosion::CreateFlash()
{
    return new Explosion(3, TextureAnim::Create( cFlash1, 0.4f, 2, 2, 4), 0.6f, 0.4f );
}


Explosion::Explosion(int numParticles, TextureAnimPtr texAnim
                     , float duration, float radius, float bilboardSize)
	: m_t(0)
	, duration(0)
	, radius(0)
    , renderer(numParticles, texAnim)
{
    this->duration = duration;
    this->radius = radius;
    this->bilboardSize = bilboardSize;

    textureAnim = texAnim;

    Particles.resize(numParticles);
    Restart();
}

Explosion::~Explosion(void)
{
}

#define FLOAT_RAND_ONE ( ((float)(rand()%1000))/500.0f -1.0f )

void	Explosion::ResetParticle(Particle* p)
{
	p->t = -duration*0.2f*FLOAT_RAND_ONE;
    p->speed = QVector3D( FLOAT_RAND_ONE - 0.5f , FLOAT_RAND_ONE - 0.5f , FLOAT_RAND_ONE - 0.5f).normalized();
	p->speed *= (radius/textureAnim->AnimDT);
}

void	Explosion::Restart()
{
	m_t=0;
    for(int i=0; i<Particles.size(); ++i)
		ResetParticle(&Particles[i]);
}


QVector3D	Explosion::GetPos()
{
	//if (!!targetUnit)		return targetUnit->GetPos();
	return Entity::GetPos();
}

bool	Explosion::IsFinished()
{
	if (m_t>duration  )
	{
		return true;
	}
	return false;
}

void	Explosion::Update(float dt)
{
	m_t += dt;	
    if (m_t>duration)
    { Restart(); return; }

    for(int i=0; i<Particles.size(); ++i)
	{
		Particle* p = &Particles[i];
		p->t += dt;
		if (p->t>0)
		{
			p->pos = GetPos() + p->speed*p->t;
            p->animFrameIndex = textureAnim->CalcCellIdx( p->t );
		}
        else	ResetParticle(p);
    }
}

void Explosion::UpdateQuadsFromParticles(QVector3D screenRight, QVector3D screenUp)
{
    QVector3D halfX = screenRight*(0.5f*bilboardSize);
    QVector3D halfY = screenUp*(0.5f*bilboardSize);

    renderer.ClearQuads();
    renderer.reserveActiveQuads(Particles.size());
    for(int i=0; i<Particles.size(); ++i)
    {
        Particle& p = Particles[i];

        ParticleQuad &quad = renderer.getQuad(i);
        textureAnim->CalcUVs( p.animFrameIndex , quad);

        quad.pos1 = p.pos - halfX - halfY; // left down
        quad.pos2 = p.pos + halfX - halfY; // right down
        quad.pos3 = p.pos + halfX + halfY; // right up
        quad.pos4 = p.pos - halfX + halfY; // left up
    }

    renderer.UpdateQuadsBuffer();
}

void	Explosion::Render(Camera &camera)
{
	if (m_t<0)	return;

    camera.moveModel( GetPos(), GetRotation() );
    UpdateQuadsFromParticles(camera.ScreenRight, camera.ScreenUp);
    renderer.RenderQuads();
}
