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

void DPIHelper::UpdateWindowed(ViewPort window)
{
    ASPECT_RATIO=1.0f;
    QScreen *screen = QApplication::screens().at(0);
    if (screen)
    {
        DPI_X = screen->physicalDotsPerInchX();
        DPI_Y = screen->physicalDotsPerInchY();
        DPI_average = (DPI_X + DPI_Y)/2.f;

        float sizeX = window.Width()/ DPI_X;
        float sizeY = window.Height()/ DPI_Y;
        bool portrait = (sizeX<sizeY);
        if (portrait)
        {
            if (sizeY>0)   ASPECT_RATIO =  DPI_X / DPI_Y;
        }
        else
        {
            if (sizeX>0)    ASPECT_RATIO =  DPI_Y / DPI_X;
        }

        qDebug() << "DPI x y aspect : " << DPI_X << DPI_Y << ASPECT_RATIO;
    }
}
