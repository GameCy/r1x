#ifndef INSTANCERENDERER_H
#define INSTANCERENDERER_H
#include <QVector3D>
#include <QQuaternion>
#include "Model.h"
#include "Camera.h"


struct Instance {
    Instance() { matrix.setToIdentity(); }
    Instance(QVector3D pos, QQuaternion rot)
    {
        matrix.setToIdentity();
        matrix.translate(pos);
        matrix.rotate(rot);
    }

    QMatrix4x4 matrix;
};


class InstanceRenderer
{
public:
    InstanceRenderer(ModelPtr model);

    void AddInstance(int meshIndex, QVector3D pos, QQuaternion rot);
    void Render(CameraPtr cam);

private:
    ModelPtr _model;

    typedef QVector<Instance>   InstanceArray;
    QVector<InstanceArray> meshInstances;
    void RenderArray(CameraPtr cam, Mesh *mesh, InstanceArray &array);
};

#endif // INSTANCERENDERER_H
