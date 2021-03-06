#include "InputArea.h"
#include "InputAreaManager.h"

InputArea::InputArea()
    : InputDisabled(false)
    , state(Normal)
    , activeEventID(0)
    , toDelete(false)
{
    uniqueAreaID = InputAreaManager::GetUniqueID();
}

bool InputArea::Contains(QVector2D p)
{
    if ( p.x()>Pos.x() && p.x()<(Pos.x()+Size.x()) &&
         p.y()>Pos.y() && p.y()<(Pos.y()+Size.y()) )
        return true;
    return false;
}

void InputArea::SetState(InputArea::State newState, QVector2D lastMousePos, int eventID)
{
    if (activeEventID!=0 && eventID!=activeEventID)
        return;
    activeEventID = eventID;

    if (state != newState )
    {
        emit StateChanged(newState, state, this, lastMousePos);
        state = newState;
    }
    else
    {
        emit MoveUpdate(state, state, this, lastMousePos);
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

void InputArea::DeleteLater()
{
    toDelete=true;
}
