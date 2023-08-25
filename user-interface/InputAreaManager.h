#pragma once
#include "InputArea.h"
#include "FocusGuard.h"
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

    void SetFocusArea(FocusGuard* occupier);

    static uint GetUniqueID();
private:
    QList<InputArea*>  areas;
    QList<InputArea*>  activeAreas;
    FocusGuard *focusArea;

    InputAreaManager();

    static InputAreaManager* instance;
    static uint uniqueIDCounter;
};
