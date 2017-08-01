#include "TextureManager.h"
#include <QDebug>


TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
    textures.clear();
}

TexturePtr TextureManager::Get(QString name)
{
    TexturePtr found;
    if (name.isEmpty())
        return 0;

    found = textures.value(name, 0);
    if (!found)
    {
        found = new Texture( QImage(name));
        if (!found || !found->isCreated())
        {
            qDebug() << "failed to load " << name;
            return 0;
        }
        qDebug() << "texture loaded " << name;

        textures[name] = found;
    }
    return found;
}

void TextureManager::Release(QString name)
{
    if (textures.contains(name))
        textures.remove(name);
}

void TextureManager::ClearAll()
{
    textures.clear();
}
