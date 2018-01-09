#ifndef FONTRENDERER_H
#define FONTRENDERER_H
#include "SmartPtr.h"
#include "TextLabel.h"

class TextRenderer : public RefCountBase
{
public:
    TextRenderer(FontPtr font);

    void    ClearAllLabels();
    TextLabelPtr CreateLabel(QString text, QVector2D pos);
    void    RemoveLabel(TextLabelPtr label);

    void    BuildQuads();

    virtual void	Render();
    virtual void	Update();

private:
    QList<TextLabelPtr> labels;
    QuadRenderer3D      *quadRenderer;
    FontPtr             fontRef;
};

typedef SmartPtr<TextRenderer> FontRendererPtr;

#endif // FONTRENDERER_H
