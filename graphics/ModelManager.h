#ifndef MODELMANAGER_H
#define MODELMANAGER_H
#include <QMap>
#include <QString>
#include "Model.h"


class ModelManager
{
public:
    ModelManager();
    ~ModelManager();

    ModelPtr Get(QString modelUrl);
    void    Release(ModelPtr model);

    void ClearAll();

private:
    QMap<QString, ModelPtr>   models;
};

#endif // MODELMANAGER_H
