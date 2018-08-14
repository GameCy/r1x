#include "Icon.h"
#include <QDebug>
#include "InputAreaManager.h"

Icon::Icon(QString iconSpriteName, QString overlayName, SpriteMapPtr uiMap, UVRect uvRect)
{
    TexUVArea = uvRect;
    Background = uiMap->CreateSprite(iconSpriteName);
    Background->setUVRect( uvRect );

    if (overlayName.isEmpty())
        Overlay=0;
    else
        Overlay = uiMap->CreateSprite(overlayName);

    ChangeVisuals(Normal, Normal, this);
    UpdateInternals();
    connect( this, &InputArea::StateChanged, this, &Icon::ChangeVisuals);
    InputAreaManager::Instance().Add(this);
}

Icon::~Icon()
{
    Background->DeleteLater();
    Overlay->DeleteLater();
    disconnect( this, &InputArea::StateChanged, this, &Icon::ChangeVisuals);
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

void Icon::Hide()
{
    Background->SetVisible(false);
    Overlay->SetVisible(false);
    InputDisabled=true;;
}
void Icon::Show()
{
    Background->SetVisible(true);
    Overlay->SetVisible(true);
    InputDisabled=true;;
}

void Icon::UpdateInternals()
{
    Background->setPos(Pos);
    Background->setSize(Size);

    if (Overlay)
    {
        Overlay->setPos(Pos+Size*0.2f);
        Overlay->setSize(Size*0.6f);
    }
}

void Icon::ChangeVisuals(InputArea::State newState, InputArea::State oldState, InputArea* sender)
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
