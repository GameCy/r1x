#ifndef MODELMANAGER_H
#define MODELMANAGER_H
#include <QVector>
#include <QString>
#include "Model.h"

enum ModelNames {
    Model_Warrior,
    Model_Warrior2,
    Model_Circle,
    Model_Arrows,
    Model_NavigationMarks,
    Model_HealthMarks,
    Model_Theme1,
    Model_MAX_ID
};

class ModelManager
{
public:
    ModelManager();
    ~ModelManager();

    ModelPtr Get(ModelNames name);
    void    Release(ModelNames name);

    void ClearAll();

private:
    QVector<ModelPtr>   models;
    QVector<QString>    resource_paths;
    void    BuildResourcePaths();
};

#endif // MODELMANAGER_H
