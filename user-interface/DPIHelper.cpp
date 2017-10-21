#include "DPIHelper.h"
#include <QApplication>
#include <QScreen>
//#include <QDebug>

//DPIHelper::DPIHelper()
//{
    //qreal pxDPI = screen->physicalDotsPerInchX();
    //qreal pyDPI = screen->physicalDotsPerInchY();
    //QRect localGeometry = screen->geometry();
//}

float DPIHelper::GetPhysicalAspectRatio()
{
    float aspect=1.0f;
    QScreen *screen = QApplication::screens().at(0);
    if (screen)
    {
        qreal pxDPI = screen->physicalDotsPerInchX();
        qreal pyDPI = screen->physicalDotsPerInchY();

        //QSizeF physicalSize = screen->physicalSize();
        if (pyDPI>0) //physicalSize.height()>0)
            aspect =  pxDPI/pyDPI; //(physicalSize.width() / physicalSize.height());

        //qDebug() << "DPI x y aspect : " << pxDPI << pyDPI << aspect;
    }
    return aspect;
}
