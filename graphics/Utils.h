#ifndef UTILS_H
#define UTILS_H
#include <QString>

class Utils
{
public:
    Utils();

    static QString     getFile(QString fullpath);
    static QString     getFolder(QString fullpath);

};

#endif // UTILS_H
