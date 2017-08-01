#include "ModelManager.h"



ModelManager::ModelManager()
{
    models.clear();
    for(int i=0; i<Model_MAX_ID; ++i)
    {
        models.push_back(0);
    }
    BuildResourcePaths();
}

ModelManager::~ModelManager()
{
    models.clear();
}

ModelPtr ModelManager::Get(ModelNames name)
{
    if (name<0 || name>=Model_MAX_ID)
        return 0;
    if (models[name]==0)
    {
        ModelPtr model = new Model();
        if (model->LoadFile( resource_paths[name] ))
            models[name] = model;
    }
    return models[name];
}

void ModelManager::Release(ModelNames name)
{
    if (name>=0 && name<Model_MAX_ID && (models[name]!=0) )
    {
        models[name] = 0;
    }
}

void ModelManager::ClearAll()
{
    models.clear();
}

void ModelManager::BuildResourcePaths()
{
    resource_paths.clear();

    resource_paths.push_back(":/fattyDefender/fattyDefender.obj");
    resource_paths.push_back(":/hornsavatar/hornsAvatar.obj");
    resource_paths.push_back(":/groundMarks/circle.obj");
    resource_paths.push_back(":/groundMarks/arrows.obj");
    resource_paths.push_back(":/groundMarks/teamControls.obj");
    resource_paths.push_back(":/groundMarks/healthMarks.obj");
    resource_paths.push_back(":/theme1/theme1.obj");
}
