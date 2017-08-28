#include "TextRenderer.h"


TextRenderer::TextRenderer(FontPtr font)
    : fontRef(font)
{
    quadRenderer = new QuadRenderer3D(2000, font->RasterMap);
}

void    TextRenderer::ClearAllLabels()
{
    labels.clear();
    quadRenderer->ClearQuads();
}

TextLabelPtr    TextRenderer::CreateLabel(QString text, QVector2D pos)
{
    TextLabelPtr label= new TextLabel(fontRef, text, pos);
    labels.push_back(label);
    return label;
}

void    TextRenderer::RemoveLabel(TextLabelPtr label)
{
    labels.removeAll(label);
}

void    TextRenderer::BuildQuads()
{
    int character=0;
    foreach (TextLabelPtr label, labels)
        character += label->Text.length();
    quadRenderer->ReserveActiveQuads(character);

    float texWidth = fontRef->RasterMap->GetTexture()->width();
    float texHeight = fontRef->RasterMap->GetTexture()->height();

    character=0;
    foreach (TextLabelPtr label, labels)
    {
        float xcursor = label->Position.x();
        float ycursor = label->Position.y();
        float scale = label->getScale();

        foreach (QChar ch, label->Text)
        {
            Symbol *symbol = fontRef->GetSymbolData( int(ch.toLatin1()) );
            if (symbol==0)
                continue;

            Quad3D &quad = quadRenderer->getQuad(character);
            symbol->CalcQuad( xcursor, ycursor, -2.0f, quad, texWidth, texHeight, scale);

            xcursor += symbol->xadvance * scale;
            character++;
        }
    }
    quadRenderer->UpdateQuadsBuffer(character);
}

void    TextRenderer::Render(CameraPtr camera)
{
    //camera.RasterMode(); // rasterMode called for all fonts once, from inside EntityManager
    quadRenderer->RenderQuads();
}

void	TextRenderer::Update(float dt)
{
    foreach (TextLabelPtr label,  labels)
    {
        if (label->isDirty)
        {
            BuildQuads();  // build all once and exit loop
            break;
        }
    }
}

bool	TextRenderer::IsFinished()  { return false; }
