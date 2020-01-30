#pragma once
#include <list>
#include <QPoint>

class Draggable;

class DropTarget
{
public:
    virtual bool IsDropedInside(QPoint pos, Draggable* source)=0;

protected:
	DropTarget()	{}
	~DropTarget()	{}
};

class DropTargetList
{
public:
    void	Add(DropTarget* dropTarget);
    void	Remove(DropTarget* dropTarget);

	std::list<DropTarget*>	List;
};

// -------------------------

class Draggable
{
public:
	Draggable(void)
        : isDragging(false), targets(nullptr)
	{}
    virtual ~Draggable(void)
	{}

    virtual bool IsInside(QPoint pos)=0;
	void	SetTargetList(DropTargetList* targetList);
    bool	IsDragging();
    QPoint GetLastPosition();
    QPoint GetDragVector();

	// manual updates
    void BeginDrag(QPoint pos);
    void UpdateDrag(QPoint pos);
    void EndDrag(QPoint pos);
	void CheckDropTargets();

protected:
    QPoint	beginDragPos;
    QPoint	lastDragPos;
    bool	isDragging;

	DropTargetList* targets;
};

typedef std::list<Draggable*>	DraggableList;

enum ButtonStates
{
    ButtonDown,
    ButtonUp,
    ActiveMotion,
    PassiveMotion,
    ButtonUndefined
};

struct MouseEventInfo
{
public:
    MouseEventInfo(int touch_id, int x, int y, ButtonStates st)
    {
        id = touch_id; pos.setX(x); pos.setY(y); state = st;
    }

	int id;
    QPoint pos;
    ButtonStates state;
};

class DragDropManager
{
public:
	DragDropManager();
	~DragDropManager();

	DraggableList Draggables;

	// handlers and delegates
	void BeginDragging(MouseEventInfo mouse);
	void UpdateDragging(MouseEventInfo mouse);
	void EndDragging(MouseEventInfo mouse);
};

extern DragDropManager* gDragDropManager;
