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

ButtonPtr UIFactory::CreateButton(QString text)
{
    UVRect uvRect;
    if (!UITexureMap->GetUVRect("button.png", uvRect))
        return 0;
    ButtonPtr btn = new Button(text, QVector2D(1,1), textRenderer, UITexureMap, uvRect);
    return btn;
}

IconPtr UIFactory::CreateIcon(QString iconSpriteName)
{
    UVRect uvRect;
    if (!UITexureMap->GetUVRect(iconSpriteName, uvRect))
        return 0;
    IconPtr icon = new Icon(iconSpriteName, QVector2D(0,0), QVector2D(8,8), UITexureMap, uvRect );
    return icon;
}

Sprite *UIFactory::CreateSprite(QString spriteName)
{
    return UITexureMap->CreateSprite(spriteName, 32, 32);
}

TextLabelPtr UIFactory::CreateLabel(QString text, QVector2D pos)
{
    return textRenderer->CreateLabel(text, pos);
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
