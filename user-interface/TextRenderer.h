#ifndef FONTRENDERER_H
#define FONTRENDERER_H
#include "SmartPtr.h"
#include "TextLabel.h"
#include "QuadRenderers.h"
#include <list>

class TextRenderer : public RefCountBase
{
public:
    TextRenderer(FontPtr font);

    void    ClearAllLabels();
    TextLabel* CreateLabel(QString text);
    void    RemoveLabel(TextLabel* label);

    void    BuildQuads();

    virtual void	Render();
    virtual void	Update();

private:
    std::list<TextLabel*> labels;
    QuadRenderer3D      *quadRenderer;
    FontPtr             fontRef;
};

typedef SmartPtr<TextRenderer> FontRendererPtr;

#endif // FONTRENDERER_H
