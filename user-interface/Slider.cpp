#include "Slider.h"
#include <QDebug>
#include "InputAreaManager.h"

Slider::Slider(QString backgroundSpriteName, QString handleName, SpriteMapPtr uiMap, bool horizontal)
    : minimum(0)
    , maximum(1.f)
    , value(.5f)
    , handleSteps(5.f)
    , handleAspect(1.f)
    , bHorizontal(horizontal)
{
    Background = uiMap->CreateSprite(backgroundSpriteName);
    Overlay = uiMap->CreateSprite(handleName);

    connect( this, &InputArea::StateChanged, this, &Slider::ChangeVisuals);
    connect( this, &InputArea::MoveUpdate, this, &Slider::ChangeVisuals);
    InputAreaManager::Instance().Add(this);
}

Slider::~Slider()
{
    this->disconnect();
    Background->DeleteLater();
    Overlay->DeleteLater();
}

void Slider::SetArea(QVector2D pos, QVector2D size)
{
    Pos = pos;
    Size = size;
    UpdateInternals();
}

void Slider::SetRange(float min, float max, float val)
{
    if (min>max)
        { minimum = max; maximum = min; }
    else
        { minimum = min;   maximum = max; }

    SetValue( val);
}

void Slider::SetHandleSize(float steps, float aspect)
{
    handleSteps = steps;
    handleAspect = aspect;
}

void Slider::SetValue(float val)
{
    if (val>maximum)        val=maximum;
    else if (val<minimum)   val = minimum;
    value = val;

    UpdateInternals();
}

void Slider::Hide()       { Background->SetVisible(false); }
void Slider::Show()       { Background->SetVisible(true); }

void Slider::UpdateInternals()
{
    Background->setPos(Pos);
    Background->setSize(Size);

    QVector2D ovSize;
    QVector2D offset;
    if (bHorizontal)
    {
        float handleSX = Size.x()/handleSteps;
        ovSize = QVector2D( handleSX, handleAspect*handleSX );

        offset.setX( value*Size.x()/(maximum-minimum) - 0.5f*handleSX);
        offset.setY( .5f*(Size.y() - ovSize.y()) );
    }
    else
    {
        float handleSY = Size.y()/handleSteps;
        ovSize = QVector2D( handleAspect*handleSY, handleSY );

        offset.setX( .5f*(Size.x() - ovSize.x()) );
        offset.setY( value*Size.y()/(maximum-minimum) - 0.5f*handleSY);
    }
    Overlay->setPos(Pos+offset);
    Overlay->setSize( ovSize );
}

void Slider::ChangeVisuals(InputArea::State newState, InputArea::State oldState
                         , InputArea* sender, QVector2D lastMousePos)
{
    if ( (oldState==InputArea::Normal) && (newState==InputArea::Pressed) )
    {
        beginPos = lastMousePos;
        beginValue = value;
        return;
    }
//    if ( newState==InputArea::Hover)
//        return;

    float slideValue=0;
    if (bHorizontal)
    {
        float slidePixels = lastMousePos.x() - beginPos.x();
        slideValue = slidePixels*(maximum - minimum)/Size.x();
    }
    else
    {
        float slidePixels = lastMousePos.y() - beginPos.y();
        slideValue = slidePixels*(maximum - minimum)/Size.y();
    }
    SetValue( beginValue + slideValue );

    bool sliderReleased = ((oldState!=Normal) && (newState==Normal));
    emit ValueChanging(value, sliderReleased);
}
