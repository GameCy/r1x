#ifndef FONTRENDERER_H
#define FONTRENDERER_H
#include "Entity.h"
#include "TextLabel.h"


class TextRenderer : public Entity
{
public:
    TextRenderer(FontPtr font);

    void    ClearAllLabels();
    TextLabelPtr CreateLabel(QString text, QVector2D pos);
    void    RemoveLabel(TextLabelPtr label);

    void    BuildQuads();

    virtual void	Render(CameraPtr camera);
    virtual void	Update(float dt);
    virtual bool	IsFinished();

private:
    QList<TextLabelPtr> labels;
    QuadRenderer3D      *quadRenderer;
    FontPtr             fontRef;
};

typedef SmartPtr<TextRenderer> FontRendererPtr;

#endif // FONTRENDERER_H
