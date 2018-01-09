#ifndef BASICMODEL_H
#define BASICMODEL_H
#include "Entity.h"

class BasicModel : public Entity
{
public:
    BasicModel(ModelPtr model);

    // Entity interface
    void Render(CameraPtr camera);
    void Update(float dt);
    bool IsFinished();

    bool Hidden;
};

typedef SmartPtr<BasicModel> BasicModelPtr;
//typedef BasicModel* BasicModelPtr;

#endif // BASICMODEL_H
