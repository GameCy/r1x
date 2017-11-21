#include "InputArea.h"
#include "ButtonManager.h"

InputArea::InputArea()
    : state(Normal)
    , activeEventID(0)
{
}

bool InputArea::Contains(QVector2D p)
{
    if ( p.x()>Pos.x() && p.x()<(Pos.x()+Size.x()) &&
         p.y()>Pos.y() && p.y()<(Pos.y()+Size.y()) )
        return true;
    return false;
}

void InputArea::SetState(InputArea::State newState, int eventID)
{
    if (activeEventID!=0 && eventID!=activeEventID)
        return;
    activeEventID = eventID;

    if (state != newState)
    {
        emit StateChanged(newState, state);
        state = newState;
    }
}

void InputArea::ClearActiveID()
{
    activeEventID = 0;
}

bool InputArea::IsSameEventId(int id)
{
    return (activeEventID==id);
}

void InputArea::Enable()     { ButtonManager::Instance().Add(this); }
void InputArea::Disable()    { ButtonManager::Instance().Remove(this); }
