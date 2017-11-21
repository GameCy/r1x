#include "DPIHelper.h"
#include <QApplication>
#include <QScreen>
#include <QDebug>


void DPIHelper::Update()
{
    ASPECT_RATIO=1.0f;
    QScreen *screen = QApplication::screens().at(0);
    if (screen)
    {
        DPI_X = screen->physicalDotsPerInchX();
        DPI_Y = screen->physicalDotsPerInchY();
        DPI_average = (DPI_X + DPI_Y)/2.f;

        QSizeF physicalSize = screen->physicalSize();
        float sizeX = physicalSize.width()/ DPI_X;
        float sizeY = physicalSize.height()/ DPI_Y;
        bool portrait = (sizeX<sizeY);
        if (portrait)
        {
            if (sizeY>0)   ASPECT_RATIO =  sizeX / sizeY;
        }
        else
        {
            if (sizeX>0)    ASPECT_RATIO =  sizeY / sizeX;
        }

        qDebug() << "DPI x y aspect : " << DPI_X << DPI_Y << ASPECT_RATIO;
    }
}
