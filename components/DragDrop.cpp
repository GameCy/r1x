#include "DragDrop.h"

void DropTargetList::Add(DropTarget* dropTarget)
{
	List.push_back(dropTarget);
}

void DropTargetList::Remove(DropTarget* dropTarget)
{
	List.remove(dropTarget);
}

// -----------------------------------------

QPoint Draggable::GetLastPosition()
{
	return lastDragPos;
}

QPoint Draggable::GetDragVector()
{
	return (lastDragPos - beginDragPos);
}

bool Draggable::IsDragging()
{
	return isDragging;
}

// manual updates
void Draggable::BeginDrag(QPoint pos)
{
	beginDragPos = lastDragPos = pos;
	isDragging = true;
}

void Draggable::UpdateDrag(QPoint pos)
{
	lastDragPos = pos;
}

void Draggable::EndDrag(QPoint pos)
{
	lastDragPos = pos;
	isDragging = false;
}

void Draggable::SetTargetList(DropTargetList* targetList)
{
	 targets = targetList;
}

void Draggable::CheckDropTargets()
{
	std::list<DropTarget*>::iterator itr;
	for(itr=targets->List.begin(); itr!=targets->List.end(); ++itr)
	{
		if ((*itr)->IsInside(lastDragPos, this))
			break;
	}
}

// ---------------------------------

DragDropManager* gDragDropManager=nullptr;

DragDropManager::DragDropManager()
{
}

DragDropManager::~DragDropManager()
{
}

void DragDropManager::BeginDragging(MouseEventInfo mouse)
{
	DraggableList::iterator itr;
	for(itr=Draggables.begin(); itr!=Draggables.end(); ++itr)
        if (!(*itr)->IsDragging() && (*itr)->IsInside(mouse.pos))
		{
            (*itr)->BeginDrag( mouse.pos );
			break; // added in code review , not tested. ideally drag only 1 obj
		}
			
}

void DragDropManager::UpdateDragging(MouseEventInfo mouse)
{
	DraggableList::iterator itr;
	for(itr=Draggables.begin(); itr!=Draggables.end(); ++itr)
		if ((*itr)->IsDragging() ) // here check touch_id, not just true false
            (*itr)->UpdateDrag( mouse.pos );
}

void DragDropManager::EndDragging(MouseEventInfo mouse)
{
	DraggableList::iterator itr;
	for(itr=Draggables.begin(); itr!=Draggables.end(); ++itr)
		if ((*itr)->IsDragging() ) // likewise, end drag of touch_id , in case multi drag
		{
            (*itr)->EndDrag(mouse.pos);
			(*itr)->CheckDropTargets();
		}
}
