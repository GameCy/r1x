#pragma once
#include "SpriteMap.h"
#include "InputArea.h"
#include <QString>
#include <QVector3D>
#include <QObject>

class Slider: public InputArea
{
    Q_OBJECT
public:
    Slider(QString backgroundSpriteName, QString handleName, SpriteMapPtr uiMap, bool horizontal);
    ~Slider();

    void    SetArea(QVector2D bgPos, QVector2D bgSize, float usableSlidePercentage);
    void    SetArea(QVector2D pos, QVector2D size);
    void    SetRange(float min, float max, float val);
    void    SetHandleSize(float steps, float aspect);
    void    SetValue(float val);

    void    Hide();
    void    Show();

    Sprite* Background;
    Sprite* Overlay;
private:
    UVRect  TexUVArea ;
    float   minimum, maximum, value;
    float   handleSteps, handleAspect;
    bool    bHorizontal;

    void UpdateOverlay();
    QVector2D   beginPos;
    float       beginValue;

signals:
    void    ValueChanging(float value, bool  released);

private slots:
    void ChangeVisuals(InputArea::State newState, InputArea::State oldState
                       ,InputArea* sender, QVector2D lastMousePos);

};
