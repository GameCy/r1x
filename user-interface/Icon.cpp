#include "Icon.h"
#include <QDebug>
#include "ButtonManager.h"

Icon::Icon(QString iconSpriteName, QVector2D pos, QVector2D iconSize, SpriteMapPtr uiMap, UVRect uvRect)
{
    TexUVArea = uvRect;
    Background = uiMap->CreateSprite(iconSpriteName, 0,0);
    Background->setUVRect( uvRect );
    Background->setSize(iconSize);
    ChangeVisuals(Normal, Normal);

    UpdateInternals();
    connect( this, &InputArea::StateChanged, this, &Icon::ChangeVisuals);
    ButtonManager::Instance().Add(this);
}

Icon::~Icon()
{
    disconnect( this, &InputArea::StateChanged, this, &Icon::ChangeVisuals);
    ButtonManager::Instance().Remove(this);
}

void Icon::SetPos(QVector2D pos)
{
    Pos = pos;
    UpdateInternals();
}

void Icon::SetSize(QVector2D size)
{
    Size = size;
    UpdateInternals();
}

void Icon::Hide()       { Background->SetVisible(false); }
void Icon::Show()       { Background->SetVisible(true); }

void Icon::UpdateInternals()
{
    Background->setPos(Pos);
    Background->setSize(Size);
}

void Icon::ChangeVisuals(InputArea::State newState, InputArea::State oldState)
{
    float Vheight = TexUVArea.V2 - TexUVArea.V1;
    float deltaV = 0;
    if (newState==InputArea::Pressed)       deltaV += 0.33333f*Vheight;
    else if (newState==InputArea::Hover)    deltaV += 0.66666f*Vheight;

    UVRect newRect = TexUVArea;
    newRect.V1 += deltaV;
    newRect.V2 = newRect.V1 + 0.33333f*Vheight;
    Background->setUVRect( newRect );
}
