#include "SmokeTrail.h"
#include <math.h>

#define FLOAT_RAND_HALF ( ((float)(rand()%1000))/1000.0f -0.5f )

SmokeTrail::SmokeTrail(int numParticles, TextureAnimPtr texAnim
                     , float duration, float radius, float bilboardSize)
    : duration(duration)
    , radius(radius)
    , bilboardSize(bilboardSize)
    , renderer(numParticles, texAnim)
    , finished(false)
{
    textureAnim = texAnim;
    Particles.reserve( numParticles );
}

SmokeTrail::~SmokeTrail(void)
{
}

void    SmokeTrail::TerminateTrail()
{
    finished = true;
}

void    SmokeTrail::setTrackedTarget(EntityPtr target)
{
    this->trackedTarget = target;
}

void	SmokeTrail::trackTargetAddParticle()
{
    if (!trackedTarget)
        return;
    QVector3D pos = trackedTarget->GetPos();
    if (lastPos.distanceToPoint( pos)<bilboardSize)
        return;

    Particle p;
    p.pos = pos;
    p.t = 0.0f;
    p.speed = QVector3D( FLOAT_RAND_HALF , 1.0f, FLOAT_RAND_HALF).normalized();
    p.speed *= (radius/textureAnim->AnimDT);

    Particles.push_back(p);
    lastPos = pos;
}

QVector3D	SmokeTrail::GetPos()
{
	//if (!!targetUnit)		return targetUnit->GetPos();
	return Entity::GetPos();
}

bool	SmokeTrail::IsFinished()
{
    if (finished && Particles.size()==0 )
	{
		return true;
	}
	return false;
}

void	SmokeTrail::Update(float dt)
{
    trackTargetAddParticle( );

    std::vector<Particle>::iterator particle;
    for(particle=Particles.begin(); particle!=Particles.end(); /*no increment*/)
	{
        particle->t += dt;
        if (particle->t > duration)
        {
            particle = Particles.erase(particle);
        }
        else
		{
            particle->pos += particle->speed*dt;
            particle->animFrameIndex = textureAnim->CalcCellIdx( particle->t );
            ++particle;
		}
    }
}

void SmokeTrail::UpdateQuadsFromParticles(QVector3D screenRight, QVector3D screenUp)
{
    QVector3D halfX = screenRight*(0.5f*bilboardSize);
    QVector3D halfY = screenUp*(0.5f*bilboardSize);

    renderer.ClearQuads();
    renderer.reserveActiveQuads(Particles.size());

    int quadIdx=0;
    std::vector<Particle>::iterator particle;
    for(particle=Particles.begin(); particle!=Particles.end(); ++particle)
    {
        ParticleQuad &quad = renderer.getQuad(quadIdx);
        quadIdx++;
        textureAnim->CalcUVs( particle->animFrameIndex , quad);

        QVector3D pos = particle->pos;
        quad.pos1 = pos - halfX - halfY; // left down
        quad.pos2 = pos + halfX - halfY; // right down
        quad.pos3 = pos + halfX + halfY; // right up
        quad.pos4 = pos - halfX + halfY; // left up
    }

    renderer.UpdateQuadsBuffer();
}

void	SmokeTrail::Render(Camera &camera)
{
    camera.moveModel( QVector3D(), QQuaternion() );
    UpdateQuadsFromParticles(camera.ScreenRight, camera.ScreenUp);
    renderer.RenderQuads();
}
