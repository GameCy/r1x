#include "Icon.h"
#include "ButtonManager.h"
#include <QDebug>

Icon::Icon(QString iconSpriteName, QVector2D pos, QVector2D iconSize, SpriteMapPtr uiMap, UVRect uvRect)
{
    TexUVArea = uvRect;
    Background = uiMap->CreateSprite(iconSpriteName, 0,0);
    Background->setUVsize( QVector2D(uvRect.U2-uvRect.U1, (uvRect.V2-uvRect.V1)/3.0f) );
    Background->setSize(iconSize);

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

void Icon::Enable()       { ButtonManager::Instance().Add(this); }

void Icon::Disable()      { ButtonManager::Instance().Remove(this); }

void Icon::UpdateInternals()
{
    Background->setPos(Pos);
    Background->setSize(Size);
}

void Icon::ChangeVisuals(InputArea::State newState, InputArea::State oldState)
{
    float U = TexUVArea.U1;
    float V = TexUVArea.V1;
    float Vheight = TexUVArea.V2 - TexUVArea.V1;

    if (newState==InputArea::Pressed)       V += 0.33333f*Vheight;
    else if (newState==InputArea::Hover)    V += 0.66666f*Vheight;
    Background->setUVstart( QVector2D(U,V) );
}



