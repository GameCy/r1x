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

    Button* CreateButton(QString text);
    Icon*   CreateIcon(QString iconSpriteName, QString overlayName);
    Sprite* CreateSprite(QString spriteName);
    TextLabel* CreateLabel(QString text);

    SpriteMapPtr    UITexureMap;
    FontRendererPtr textRenderer;

    void    Render();
    void    Update();
};

#endif // UIFACTORY_H
