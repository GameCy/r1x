#ifndef VIEWD3DMODELS_H
#define VIEWD3DMODELS_H
#include "ExampleBase.h"
#include "Graphics.h"
#include "Camera.h"
#include "BasicModel.h"

class Viewd3DModels : public ExampleBase
{
public:
    Viewd3DModels();

    // ExampleBase interface
public:
    void Render();
    void Update(float dt);
    void Resize(float w, float h);

private:
    Camera      camera;
    ModelPtr    monkey;
    float       angle;

    BasicModel  ground;
};

#endif // VIEWD3DMODELS_H
