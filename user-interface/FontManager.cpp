#include "FontManager.h"
#include <QDebug>


FontManager::FontManager()
{

}

bool FontManager::LoadFont(QString name, QString path)
{
    if (name.isEmpty())
        return false;

    if (!(fonts.value(name, 0)))
        fonts[name] = new Font( path );

    return true;
}

FontPtr FontManager::GetFont(QString name)
{
    if (name.isEmpty())
        return 0;
    return fonts.value(name, 0);
}

FontRendererPtr FontManager::GetRenderer(QString name)
{
    if (name.isEmpty())
        return 0;
    return new FontRenderer( fonts.value(name, 0) );
}

void FontManager::ClearAll()
{
    fonts.clear();
}

void FontManager::Release(QString name)
{
    if (fonts.contains(name))
        fonts.remove(name);
}
