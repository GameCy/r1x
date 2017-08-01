#pragma once
#include "SpriteMap.h"
#include "Font.h"
#include "InputArea.h"
#include <QString>
#include <QVector3D>
#include "Font.h"
#include <QObject>
#include <QtWidgets>

class Button : public InputArea
{
    Q_OBJECT
public:
    Button(QString txt, QVector2D pos, FontRendererPtr fontRenderer, SpriteMapPtr uiMap, UVRect uvRect);
    ~Button();

    void    SetText(QString text);
    void    SetPos(QVector2D pos);
    void    SetSize(QVector2D size);
    void    SetTextScale(float scale);

    void    Enable();
    void    Disable();
private:
    TextLabelPtr Label;
    SpritePtr   Background;
    UVRect      TexUVArea ;

    void UpdateInternals();

private slots:
    void ChangeVisuals(InputArea::State newState, InputArea::State oldState);
};

//typedef SmartPtr<Button>    ButtonPtr;
typedef Button*    ButtonPtr;
