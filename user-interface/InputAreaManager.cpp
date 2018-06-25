#include "InputAreaManager.h"
#include "Camera.h"
#include "Graphics.h"

InputAreaManager* InputAreaManager::instance=0;
uint InputAreaManager::uniqueIDCounter=0;

InputAreaManager &InputAreaManager::Instance()
{
    if(instance==0)
        instance = new InputAreaManager();
    return (*instance);
}

void InputAreaManager::Add(InputArea* area)
{
    if (area->toDelete)
        return;
    if (areas.contains(area) )
        return;
    areas.push_back(area);
}

void InputAreaManager::Remove(InputArea* area)
{
    areas.removeAll(area);
}

void InputAreaManager::ExecuteRemovals()
{
    auto itr = areas.begin();
    while (itr!=areas.end())
    {
        InputArea* area = (*itr);
        if (area->toDelete)
        {
            itr = areas.erase(itr);
            qDebug() << "deleting InputArea: " << area << "uid: " << area->uniqueAreaID;
            delete area;
        }
        else
            itr++;
    }
    itr = activeAreas.begin();
    while (itr!=activeAreas.end())
    {
        InputArea* area = (*itr);
        if (area->toDelete)
        {
            itr = areas.erase(itr);
            qDebug() << "deleting InputArea: " << area<< "uid: " << area->uniqueAreaID;
            delete area;
        }
        else
            itr++;
    }
}

void InputAreaManager::TapBeginHandler(int id, QVector2D pos)
{
    auto itr = areas.begin();
    while( itr!=areas.end())
    {
        InputArea* area =  (*itr);
        if ((!area->InputDisabled) && area->Contains(pos))
        {
            qDebug() << "tap Begin: " << area << "uid: " << area->uniqueAreaID;

            activeAreas.push_back( area );
            areas.erase(itr);
            area->SetState(InputArea::Pressed, pos, id);
            return;
        }
        ++itr;
    }
}

void InputAreaManager::TapEndHandler(int id, QVector2D pos)
{
    auto itr = activeAreas.begin();
    while(itr!=activeAreas.end())
    {
        InputArea* area = (*itr);
        if (area->IsSameEventId(id))
        {
            qDebug() << "tap End: " << area << "uid: " << area->uniqueAreaID;

            area->SetState(InputArea::Normal, pos, id);
            area->ClearActiveID();
            if (area->Contains(pos) && (!area->InputDisabled))
                emit area->Clicked(area, pos);

            areas.push_back( area );
            activeAreas.erase(itr);
            return;
        }
        ++itr;
    }
}

void InputAreaManager::TapMoveHandler(int id, QVector2D pos)
{
    auto itr = activeAreas.begin();
    for(; itr!=activeAreas.end(); ++itr)
    {
        InputArea* area = (*itr);
        InputArea::State newState = (area->Contains(pos)) ? InputArea::Pressed : InputArea::Hover;
        area->SetState(newState, pos, id);
        // if (!area->InputDisabled) //  emit ....
    }
}

uint InputAreaManager::GetUniqueID()
{
    return uniqueIDCounter++;
}

