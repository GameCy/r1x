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
    virtual ~Viewd3DModels();

    // Temporal interface
    void Update(float dt);
    // ExampleBase interface
    void Render();
    void Resize(float w, float h);

private:
    Camera      camera;
    ModelPtr    monkey;

    BasicModel  ground;
};

#endif // VIEWD3DMODELS_H
