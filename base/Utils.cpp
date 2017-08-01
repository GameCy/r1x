#include "base/Utils.h"

Utils::Utils()
{

}

QString Utils::getFolder(QString fullpath)
{
    int SlashIndex = fullpath.lastIndexOf("/");

    if (SlashIndex <0)          return ".";
    else if (SlashIndex == 0)   return "/";
    else                        return fullpath.mid(0, SlashIndex);
}
