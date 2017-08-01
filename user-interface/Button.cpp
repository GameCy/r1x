#include "Button.h"
#include "ButtonManager.h"
#include <QDebug>

Button::Button(QString txt, QVector2D pos, FontRendererPtr fontRenderer, SpriteMapPtr uiMap, UVRect uvRect)
{
    TexUVArea = uvRect;
    Label = fontRenderer->CreateLabel(txt, pos);
    Background = uiMap->CreateSprite("button.png", 0,0);
    Background->setUVsize( QVector2D(uvRect.U2-uvRect.U1, (uvRect.V2-uvRect.V1)/3.0f) );
    Background->setSize( QVector2D(Label->PixelWidth, Label->PixelHeight) *1.1f );

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

void Button::Enable()       { ButtonManager::Instance().Add(this); }

void Button::Disable()      { ButtonManager::Instance().Remove(this); }

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
    float U = TexUVArea.U1;
    float V = TexUVArea.V1;
    float Vheight = TexUVArea.V2 - TexUVArea.V1;

    if (newState==InputArea::Pressed)       V += 0.33333f*Vheight;
    else if (newState==InputArea::Hover)    V += 0.66666f*Vheight;
    Background->setUVstart( QVector2D(U,V) );
}



