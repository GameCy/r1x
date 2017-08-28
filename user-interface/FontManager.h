#ifndef FONTMANAGER_H
#define FONTMANAGER_H
#include "Font.h"
#include <QMap>

class FontManager
{
public:
    FontManager();

    bool    LoadFont(QString name, QString path);
    void    Release(QString name);

    FontPtr Get(QString name);

    void ClearAll();
private:
    QMap<QString, FontPtr>   fonts;
};

#endif // FONTMANAGER_H

