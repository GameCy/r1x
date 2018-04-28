#include "Button.h"
#include <QDebug>
#include "ButtonManager.h"

Button::Button(QString txt, FontRendererPtr fontRenderer, Sprite* backgroundsSprite, UVRect uvRect)
{
    textScale = 1.f;
    TexUVArea = uvRect;
    Label = fontRenderer->CreateLabel(txt);
    Background = backgroundsSprite;
    SetSize( QVector2D(Label->PixelWidth*1.2f, Label->PixelHeight) *1.2f );
    UpdateGeometry();
    ChangeVisuals(Normal, Normal, this);

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
    UpdateGeometry();
}

void Button::SetPos(QVector2D pos)
{
    Pos = pos;
    UpdateGeometry();
}

void Button::SetSize(QVector2D size)
{
    Size = size;
    UpdateGeometry();
}

void Button::SetTextScale(float scale)
{
    textScale = scale;
    //Label->setScale(textScale);
    UpdateGeometry();
}

void Button::UpdateGeometry()
{
    Background->setPos(Pos);
    Background->setSize(Size);

    float scale = textScale * (Size.x() / Label->PixelWidth);
    Label->setScale( scale );
    float xOffset = (Size.x() - Label->PixelWidth)/2.f;
    float yOffset = (Size.y() - Label->PixelHeight)/2.f;
    Label->SetPos(Pos + QVector2D(xOffset, yOffset) );

}

void Button::ChangeVisuals(InputArea::State newState, InputArea::State oldState, InputAreaPtr sender)
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
