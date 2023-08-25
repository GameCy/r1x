#ifndef FOCUSGUARD_H
#define FOCUSGUARD_H
#include <QVector2D>

class FocusGuard
{
public:
    virtual bool outsideFocusArea(QVector2D p)=0;
};

#endif // FOCUSGUARD_H
