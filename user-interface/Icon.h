#pragma once
#include "SpriteMap.h"
#include "InputArea.h"
#include <QString>
#include <QVector3D>
#include <QObject>

class Icon: public InputArea
{
    Q_OBJECT
public:
    Icon(QString iconSpriteName, QVector2D pos, QVector2D iconSize, SpriteMapPtr uiMap, UVRect uvRect);
    ~Icon();

    void    SetPos(QVector2D pos);
    void    SetSize(QVector2D size);

    void    Hide();
    void    Show();

private:
    Sprite*     Background;
    UVRect      TexUVArea ;

    void UpdateInternals();

private slots:
    void ChangeVisuals(InputArea::State newState, InputArea::State oldState);
};

//typedef SmartPtr<Button>    ButtonPtr;
typedef Icon*    IconPtr;
