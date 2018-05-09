#include "ButtonManager.h"
#include "Camera.h"
#include "Graphics.h"
#include <QDebug>

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
    qDebug() << "InputArea Added" << area;
}

void ButtonManager::Remove(InputAreaPtr area)
{
    qDebug() << "InputArea toRemove" << area;
    toRemove.append(area);
}

void ButtonManager::ExecuteRemovals()
{
    if (toRemove.size()>0)
        qDebug() << "InputArea Removals:" << toRemove.size();
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
            (*itr)->SetState(InputArea::Pressed, pos, id);
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

