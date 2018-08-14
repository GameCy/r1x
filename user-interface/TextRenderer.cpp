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

TextLabel *TextRenderer::CreateLabel(QString text)
{
    TextLabel* label= new TextLabel(fontRef, text);
    labels.push_back(label);
    return label;
}

void    TextRenderer::RemoveLabel(TextLabel *label)
{
    labels.remove(label);
}

void    TextRenderer::BuildQuads()
{
    int character=0;
    foreach (TextLabel* label, labels)
        character += label->Text.length();
    quadRenderer->ReserveActiveQuads(character);

    float texWidth = fontRef->RasterMap->GetTexture()->width();
    float texHeight = fontRef->RasterMap->GetTexture()->height();

    auto *config = fontRef->GetConfig();
    int baseline = config->charHeight - config->base;
    character=0;
    foreach (TextLabel* label, labels)
    {
        float scale = label->getScale();
        float xcursor = label->Position.x();
        float ycursor = label->Position.y() + float(baseline)*scale;

        foreach (QChar ch, label->Text)
        {
            Symbol *symbol = fontRef->GetSymbolData(ch);
            if (symbol==nullptr)
                continue;
            Quad3D &quad = quadRenderer->getQuad(character);
            symbol->CalcQuad( xcursor, ycursor
                              , -2.0f, quad, texWidth, texHeight, scale);

            xcursor += symbol->xadvance * scale;
            character++;
        }
    }
    quadRenderer->UpdateQuadsBuffer();
}

void    TextRenderer::Render()
{
    quadRenderer->RenderQuads();
}

void	TextRenderer::Update()
{
    bool dirty=false;
    auto itr = labels.begin();
    while(itr!=labels.end())
    {
        TextLabel* label = (*itr);
        if (label->toDelete)
        {
            itr = labels.erase(itr);
            delete label;
            dirty = true;
        }
        else
        {
            if (label->isDirty)
                dirty = true;
            ++itr;
        }
    }
    if (dirty)
        BuildQuads();
}
