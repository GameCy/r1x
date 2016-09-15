#include "Biped.h"
#include "ogl.h"

Biped::Biped()
{
}

Biped::~Biped()
{
    //trail->TerminateTrail();
}

bool Biped::LoadFile(QString& Filename)
{
    bool ret = Model::LoadFile(Filename);
    leftFoot = 8; //findMesh("left_foot");
    rightFoot = 1;// findMesh("right_foot");

    return ret;
}

void Biped::Update(float dt)
{
    walk.Update(dt);
}

bool Biped::IsFinished()
{
    return false;
}

QVector3D Biped::GetPos()
{
    return walk.body;
}

void Biped::SetPos(QVector3D pos)
{
    walk.StandAt(pos);
}

void Biped::SetDirection(float dir)
{
    walk.SetDirection(dir);
}

void Biped::Render(Camera &camera)
{
    QQuaternion rot = QQuaternion::fromAxisAndAngle(0,1,0, walk.direction);

    Mesh::EnableGLAttribs();
    for (unsigned int i = 0 ; i < meshArray.size() ; i++)
    {
        if (leftFoot==i)        camera.moveModel(walk.feet[Left] , rot);
        else if (rightFoot==i)  camera.moveModel( walk.feet[Right], rot);
        else                    camera.moveModel( walk.body, rot);

        meshArray[i].Render();
    }
    Mesh::DisableGLAttribs();
}

