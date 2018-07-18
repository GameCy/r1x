#include "UIFactory.h"
#include "UI.h"

UIFactory::UIFactory(QString atlasPath, int maxSprites, QString fontName)
{
    UITexureMap = new SpriteMap(maxSprites, atlasPath);

    FontPtr font = UI::Fonts.Get(fontName);
    textRenderer = new TextRenderer( font );

    MaterialPtr uiMat = UITexureMap->GetMaterial();
    uiMat->DepthTesting = false;
    uiMat->DepthWriting = false;
    uiMat->Blending = true;
}

Button *UIFactory::CreateButton(QString text)
{
    UVRect uvRect;
    if (!UITexureMap->GetUVRect("ButtonStates.png", uvRect))
        return 0;
    Button* btn = new Button(text, textRenderer, UITexureMap->CreateSprite("ButtonStates.png"), uvRect);
    return btn;
}

Icon *UIFactory::CreateIcon(QString iconSpriteName, QString overlayName)
{
    UVRect uvRect;
    if (!UITexureMap->GetUVRect(iconSpriteName, uvRect))
        return 0;
    Icon* icon = new Icon(iconSpriteName, overlayName, UITexureMap, uvRect );
    return icon;
}

Sprite *UIFactory::CreateSprite(QString spriteName)
{
    return UITexureMap->CreateSprite(spriteName);
}

TextLabel *UIFactory::CreateLabel(QString text)
{
    return textRenderer->CreateLabel(text);
}

void UIFactory::Render()
{
    UITexureMap->Render();
    textRenderer->Render();
}

void UIFactory::Update()
{
    UITexureMap->Update();
    textRenderer->Update();
}
