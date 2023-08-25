#pragma once
#include "InputArea.h"
#include <QString>
#include <QVector3D>
#include <QObject>
#include <QtWidgets>
#include <Sprite.h>
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
    void    CenterAt(QVector2D center);
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
