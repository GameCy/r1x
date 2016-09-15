#ifndef _ICLIPPER_HEADER_
#define _ICLIPPER_HEADER_

#include <QVector3D>

class IClipper
{
public:
    virtual bool	InVisibleArea(QVector3D pos)=0;
};

#endif
