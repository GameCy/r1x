#pragma once
#include "InputArea.h"
#include <QList>

class InputAreaManager
{
public:
    static InputAreaManager& Instance();

    void Add(InputArea* area);
    void Remove(InputArea* area);
    void ExecuteRemovals();

    void TapBeginHandler(int id, QVector2D pos);
    void TapEndHandler(int id, QVector2D pos);
    void TapMoveHandler(int id, QVector2D pos);

    static uint GetUniqueID();
private:
    QList<InputArea*>  areas;
    QList<InputArea*>  activeAreas;

    InputAreaManager() {}

    static InputAreaManager* instance;
    static uint uniqueIDCounter;
};
