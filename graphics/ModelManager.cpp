#include "ModelManager.h"


ModelManager::ModelManager()
{
    models.clear();
}

ModelManager::~ModelManager()
{
    models.clear();
}

ModelPtr ModelManager::Get(QString modelUrl)
{
    if (modelUrl.isEmpty())
        return 0;
    if (models.contains(modelUrl))
        return models[modelUrl];

    ModelPtr model = new Model();
    if (model->LoadFile( modelUrl))
        models.insert(modelUrl,  model);
    else
        model = 0;

    return model;

}

void ModelManager::Release(ModelPtr model)
{
    if (!!model)
    {
        for (auto it = models.begin(); it != models.end(); )
            if (it.value() == model)
                it = models.erase(it);
            else
                ++it;
    }
}

void ModelManager::ClearAll()
{
    models.clear();
}
