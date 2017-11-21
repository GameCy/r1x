#include "Button.h"
#include <QDebug>
#include "ButtonManager.h"

Button::Button(QString txt, QVector2D pos, FontRendererPtr fontRenderer, SpriteMapPtr uiMap, UVRect uvRect)
{
    TexUVArea = uvRect;
    Label = fontRenderer->CreateLabel(txt, pos);
    Background = uiMap->CreateSprite("button.png", 0,0);
    Background->setUVRect( uvRect );
    Background->setSize( QVector2D(Label->PixelWidth, Label->PixelHeight) *1.1f );
    ChangeVisuals(Normal, Normal);

    UpdateInternals();
    connect( this, &InputArea::StateChanged, this, &Button::ChangeVisuals);
    ButtonManager::Instance().Add(this);
}

Button::~Button()
{
    disconnect( this, &InputArea::StateChanged, this, &Button::ChangeVisuals);
    ButtonManager::Instance().Remove(this);
}

void Button::SetText(QString text)
{
    Label->SetText(text);
    UpdateInternals();
}

void Button::SetPos(QVector2D pos)
{
    Pos = pos;
    UpdateInternals();
}

void Button::SetSize(QVector2D size)
{
    Size = size;
    UpdateInternals();
}

void Button::SetTextScale(float scale)
{
    Label->setScale(scale);
    UpdateInternals();
}

void Button::UpdateInternals()
{
    Background->setPos(Pos);
    Background->setSize(Size);

    float xOffset = (Size.x() - Label->PixelWidth)/2.f;
    float yOffset = (Size.y() - Label->PixelHeight)/2.f;
    Label->SetPos(Pos + QVector2D(xOffset, yOffset) );
}

void Button::ChangeVisuals(InputArea::State newState, InputArea::State oldState)
{
    float Vheight = TexUVArea.V2 - TexUVArea.V1;

    float deltaV = 0;
    if (newState==InputArea::Pressed)       deltaV += 0.33333f*Vheight;
    else if (newState==InputArea::Hover)    deltaV += 0.66666f*Vheight;

    UVRect newRect = TexUVArea;
    newRect.V1 += deltaV;
    newRect.V2 = newRect.V1+0.33333f*Vheight;
    Background->setUVRect( newRect );
}



