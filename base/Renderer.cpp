#include "Renderer.h"
#include "Assets.h"

Renderer*	Renderer::instance=0; //

Renderer& Renderer::Instance()
{
    if (instance==0)    { instance = new Renderer();  }
	return (*instance);
}

void Renderer::DestroyInstance()
{
    if (instance)	{ delete instance; instance=0; }
}

Renderer::Renderer()
{ }

Renderer::~Renderer()
{
	ForceKillAll(); 
}

void Renderer::ForceKillAll()
{
    Views.clear();
}

void Renderer::Update(float dt)
{
    foreach (auto view, Views)
    {
        BaseViewPtr v = view;
        view->Update(dt);
    }
}

void Renderer::Render()
{
    foreach (BaseViewPtr view, Views)
    {
        view->Render();
    }
}

void Renderer::resizeDisplay(int width, int height)
{
    foreach (BaseViewPtr view, Views)
    {
        view->Resize(width, height);
    }
}

