#include "ButtonManager.h"
#include "Camera.h"
#include "Graphics.h"

ButtonManager* ButtonManager::instance=0;

ButtonManager &ButtonManager::Instance()
{
    if(instance==0)
        instance = new ButtonManager();
    return (*instance);
}

void ButtonManager::Add(InputAreaPtr area)
{
    if (areas.contains(area))
        return;
    areas.push_back(area);
}

void ButtonManager::Remove(InputAreaPtr area)
{
    toRemove.append(area);
}

void ButtonManager::ExecuteRemovals()
{
    foreach(InputAreaPtr area, toRemove)
        areas.removeAll(area);
    toRemove.clear();
}

void ButtonManager::TapBeginHandler(int id, QVector2D pos)
{
    QList<InputAreaPtr>::iterator itr;
    for(itr=areas.begin(); itr!=areas.end(); ++itr)
    {
        if ((*itr)->Contains(pos))
        {
            (*itr)->SetState(InputArea::Pressed, id);
            activeAreas.push_back( (*itr) );
            areas.erase(itr);
            break;
        }
    }
}

void ButtonManager::TapEndHandler(int id, QVector2D pos)
{
    QList<InputAreaPtr>::iterator itr;
    for(itr=activeAreas.begin(); itr!=activeAreas.end(); ++itr)
    {
        if ((*itr)->IsSameEventId(id))
        {
            (*itr)->SetState(InputArea::Normal, id);
            (*itr)->ClearActiveID();

            if ((*itr)->Contains(pos))
                emit (*itr)->Clicked();

            areas.push_back( (*itr) );
            activeAreas.erase(itr);

            break;
        }
    }
}

void ButtonManager::TapMoveHandler(int id, QVector2D pos)
{
    QList<InputAreaPtr>::iterator itr;
    for(itr=activeAreas.begin(); itr!=activeAreas.end(); ++itr)
    {
        InputArea::State newState = ((*itr)->Contains(pos)) ? InputArea::Pressed : InputArea::Hover;
        (*itr)->SetState(newState, id);
    }
}

