#ifndef UIFACTORY_H
#define UIFACTORY_H
#include "Button.h"
#include "Icon.h"
#include "TextRenderer.h"
#include "TextLabel.h"

class UIFactory
{
public:
    UIFactory(QString atlasPath, int maxSprites, QString fontName);

    ButtonPtr CreateButton(QString text);
    IconPtr   CreateIcon(QString iconSpriteName);
    Sprite*   CreateSprite(QString spriteName);
    TextLabelPtr CreateLabel(QString text);

    SpriteMapPtr    UITexureMap;
    FontRendererPtr textRenderer;

    void    Render();
    void    Update();
};

#endif // UIFACTORY_H
