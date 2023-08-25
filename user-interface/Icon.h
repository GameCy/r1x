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
    Icon(QString iconSpriteName, QString overlayName, SpriteMapPtr uiMap, UVRect uvRect);
    ~Icon();

    void SetPos(QVector2D pos);
    void SetSize(QVector2D size);
    void CenterAt(QVector2D center);

    void Hide();
    void Show();

    Sprite*     Background;
    Sprite*     Overlay;
private:
    UVRect      TexUVArea ;

    void UpdateInternals();

private slots:
    void ChangeVisuals(InputArea::State newState, InputArea::State oldState, InputArea* sender);
};
