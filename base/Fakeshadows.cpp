#include "FakeShadows.h"
#include <math.h>
#include "ogl.h"

FakeShadows::FakeShadows(int maxShadows, TextureAnimPtr texAnim, float shadowSize)
    : renderer(maxShadows, texAnim)
{
}

FakeShadows::~FakeShadows(void)
{
}

void    FakeShadows::AddShadowCaster(EntityPtr entity)
{
    shadowCasters.push_back( entity );
}

void    FakeShadows::RemoveShadowCaster(EntityPtr entity)
{
    shadowCasters.remove( entity );
}

void	FakeShadows::UpdateShadowQuads()
{
    float siz = 2.0/2.0; // e.g half size

    int quadIdx=0;
    std::list<EntityPtr>::iterator itr;
    for( itr=shadowCasters.begin(); itr!=shadowCasters.end(); ++itr)
    {
        QVector3D pos = (*itr)->GetPos();
        pos.setY(0);
        ParticleQuad &quad =  renderer.getQuad(quadIdx);
        quad.pos1 = pos + QVector3D(-siz, 0,-siz);
        quad.pos2 = pos + QVector3D(-siz, 0, siz);
        quad.pos3 = pos + QVector3D( siz, 0, siz);
        quad.pos4 = pos + QVector3D( siz, 0,-siz);
        quad.UV1 = QVector2D(0,0);
        quad.UV2 = QVector2D(0,1);
        quad.UV3 = QVector2D(1,1);
        quad.UV4 = QVector2D(1,0);
        quadIdx++;
    }
    renderer.reserveActiveQuads(quadIdx);
    renderer.UpdateQuadsBuffer();
}

bool    FakeShadows::IsFinished()      { return false; }

void	FakeShadows::Update(float dt)   { }

void	FakeShadows::Render(Camera &camera)
{
    UpdateShadowQuads();
    camera.moveModel( QVector3D(0,0,0), QQuaternion() );
    ogl.glEnable(GL_BLEND);
    ogl.glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    renderer.RenderQuads();
    ogl.glDisable(GL_BLEND);
}

