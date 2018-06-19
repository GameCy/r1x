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
    {
        if (toRemove.contains(area))
            toRemove.removeAll(area);
        return;
    }
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
    QList<InputAreaPtr>::iterator itr = areas.begin();
    while( itr!=areas.end())
    {
        InputAreaPtr area =  (*itr);
        if (area->Contains(pos))
        {
            area->SetState(InputArea::Pressed, pos, id);
            activeAreas.push_back( area );
            areas.erase(itr);
            return;
        }
        ++itr;
    }
}

void ButtonManager::TapEndHandler(int id, QVector2D pos)
{
    QList<InputAreaPtr>::iterator itr;
    for(itr=activeAreas.begin(); itr!=activeAreas.end(); ++itr)
    {
        if ((*itr)->IsSameEventId(id))
        {
            InputArea* area = (*itr);
            area->SetState(InputArea::Normal, pos, id);
            area->ClearActiveID();
            if (area->Contains(pos))
                emit area->Clicked(area, pos);

            areas.push_back( area );
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
        (*itr)->SetState(newState, pos, id);
    }
}

