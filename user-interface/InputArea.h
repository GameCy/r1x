#ifndef _INPUT_AREA_
#define _INPUT_AREA_
#include <QObject>
#include <QVector2D>
#include "SmartPtr.h"

class InputArea : public QObject, public RefCountBase
{
    Q_OBJECT

public:
    InputArea();

    bool Contains(QVector2D p);

    enum State
         { Normal=0, Pressed=1, Hover=2  };

    void SetState(State newState, QVector2D lastMousePos, int eventID=0);
    void ClearActiveID();
    bool IsSameEventId(int id);
    void Enable();
    void Disable();

    QVector2D   Pos;
    QVector2D   Size;
signals:
    void Clicked(InputArea* sender, QVector2D mousePos);
    void StateChanged(InputArea::State newState, InputArea::State oldState
                     ,InputArea* sender, QVector2D lastMousePos );

protected:
    State   state;
    int     activeEventID;
};

//typedef SmartPtr<InputArea>   InputAreaPtr;
typedef InputArea*   InputAreaPtr;

#endif
