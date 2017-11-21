#pragma once
#include "InputArea.h"
#include <QList>

class ButtonManager
{
public:
    static ButtonManager& Instance();

    void Add(InputAreaPtr area);
    void Remove(InputAreaPtr area);
    void ExecuteRemovals();

    void TapBeginHandler(int id, QVector2D pos);
    void TapEndHandler(int id, QVector2D pos);
    void TapMoveHandler(int id, QVector2D pos);

private:
    QList<InputAreaPtr>  areas;
    QList<InputAreaPtr>  activeAreas;

    QList<InputAreaPtr>  toRemove;

    ButtonManager() {}

    static ButtonManager* instance;
};
