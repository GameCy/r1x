#ifndef _SCENE_MANAGER_HEADER_
#define _SCENE_MANAGER_HEADER_
#include "BaseView.h"
//#include "SmartPtr.h"
#include <list>
#include <QVector3D>
#include <QQuaternion>


class Renderer
{
public:
    static Renderer&	Instance();
    static void			DestroyInstance();

    virtual ~Renderer();

    void Update(float dt);
    void Render();

    void resizeDisplay(int width, int height);

    typedef QList<BaseViewPtr>  ViewList;
    ViewList Views;

private:
    Renderer();
    static Renderer*	instance;

    void ForceKillAll();
};

#endif
