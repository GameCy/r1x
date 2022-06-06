#include "DragDrop.h"

// -----------------------------------------

void DropTargetList::Add(DropTarget* dropTarget)
{
	List.push_back(dropTarget);
}

void DropTargetList::Remove(DropTarget* dropTarget)
{
	List.remove(dropTarget);
}

// -----------------------------------------

QVector2D Draggable::GetLastPosition()
{
	return lastDragPos;
}

QVector2D Draggable::GetDragVector()
{
	return (lastDragPos - beginDragPos);
}

bool Draggable::IsDragging()
{
    return isDragging;
}

void Draggable::SetTargetList(DropTargetList* targetList)
{
	 targets = targetList;
}

void Draggable::Update(DragStates newState, QVector2D pos, int touch_id)
{
    if (newState==Grab)
    {
        UniqueTouchId = touch_id;
        beginDragPos = pos;
    }
    if (newState==Release)
        UniqueTouchId = -1;
    lastDragPos = pos;
    if (isDragging && newState==Release)
        CheckDropTargets();
    isDragging = newState==Release? false : true;

    if (newState!=State)
    {
        State = newState;
        OnStateChanged(State);
    }
}

void Draggable::CheckDropTargets()
{
    if (!targets)
        return;
	std::list<DropTarget*>::iterator itr;
	for(itr=targets->List.begin(); itr!=targets->List.end(); ++itr)
	{
		if ((*itr)->IsInside(lastDragPos, this))
			break;
    }
}

void Draggable::OnStateChanged(DragStates newState)

{
}

// -----------------------------------------

DragDropManager *DragDropManager::instance=0;

DragDropManager *DragDropManager::Instance()
{
    if (instance==0)
    {
        instance = new DragDropManager;
    }
    return instance;
}

void DragDropManager::DestroyInstance()
{
    if (instance)
        delete instance;
}

DragDropManager::DragDropManager()
{
}

DragDropManager::~DragDropManager()
{
}

void DragDropManager::InspectDraggables(DragStates touchState, int touch_id, QVector2D pos)
{
    DraggableList::iterator itr;
    for(itr=Draggables.begin(); itr!=Draggables.end(); ++itr)
    {
        Draggable* d = (*itr);
        bool isDragging = d->IsDragging();
        if (touchState==Grab && isDragging==false && d->IsInside(pos))
        {
            d->Update(touchState, pos, touch_id );
            break; // ideally drag only 1 obj
        }
        else if (isDragging) // here check touch_id, not just true false
        {
            d->Update(touchState, pos, touch_id );
            if (touchState==Release)
                break;
        }
    }
}
