#pragma once
#include "SpriteMap.h"
#include "Font.h"
#include "InputArea.h"
#include <QString>
#include <QVector3D>
#include "Font.h"
#include <QObject>
#include <QtWidgets>
#include "TextLabel.h"
#include "TextRenderer.h"

class Button : public InputArea
{
    Q_OBJECT
public:
    Button(QString txt, FontRendererPtr fontRenderer, Sprite *backgroundsSprite, UVRect uvRect);
    ~Button();

    void    SetText(QString text);
    void    SetPos(QVector2D pos);
    void    SetSize(QVector2D size);
    void    SetTextScale(float scale);

private:
    TextLabel*  Label;
    Sprite*     Background;
    UVRect      TexUVArea ;
    float       textScale;

    void UpdateGeometry();

private slots:
    void ChangeVisuals(InputArea::State newState, InputArea::State oldState, InputArea* sender);
};
