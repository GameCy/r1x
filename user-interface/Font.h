#ifndef FONT_H
#define FONT_H
#include "FontData.h"
#include <QHash>
#include "Material.h"
#include "SmartPtr.h"


class Font : public RefCountBase
{
public:
    Font(QString filepath);

    Symbol *GetSymbolData(QChar ch);

    FontConfig* GetConfig()     { return config; }

    MaterialPtr     RasterMap;

private:
    bool    LoadTexture();
    void    symbolsGLNormalizeYOffset();

    QString     fileName;
    FontConfig *config;
    QHash<int, Symbol> symbols;
};

typedef SmartPtr<Font>  FontPtr;

#endif // FONT_H
