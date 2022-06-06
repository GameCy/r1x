#pragma once
#include <list>
#include <QVector2D>


enum DragStates     { Grab, Move, Release };

struct DragEventInfo
{
public:
    DragEventInfo(int touch_id, QVector2D pos, DragStates st)
    {
        id = touch_id; position = pos; state = st;
    }

    int id;
    QVector2D position;
    DragStates state;
};

class Draggable;

class DropTarget
{
public:
    virtual bool IsInside(QVector2D pos, Draggable* source)=0;

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
        : State(Release)
        , UniqueTouchId(-1)
        , isDragging(false)
        , targets(nullptr)
	{}
    virtual ~Draggable(void)
	{}

	void	SetTargetList(DropTargetList* targetList);
    bool	IsDragging();
    QVector2D GetLastPosition();
    QVector2D GetDragVector();

    void Update(DragStates newState, QVector2D pos, int touch_id);
    void CheckDropTargets();

    virtual bool IsInside(QVector2D pos)=0;
    virtual void OnStateChanged(DragStates newState);

    DragStates  State;
    int         UniqueTouchId;

private:
    QVector2D	beginDragPos;
    QVector2D	lastDragPos;
	bool		isDragging;

	DropTargetList* targets;

    void SetState(DragStates newState);
};

typedef std::list<Draggable*>	DraggableList;

// -----------------------------------------
class DragDropManager
{
public:
    static DragDropManager* Instance();
    static void DestroyInstance();

	DraggableList Draggables;

    void InspectDraggables(DragStates touchState, int touch_id, QVector2D pos);

private:
    static DragDropManager* instance;
    DragDropManager();
    ~DragDropManager();
};

