#include "DPIHelper.h"
#include <QApplication>
#include <QScreen>
#include <QDebug>


void DPIHelper::Update(ViewPort window)
{
    VIEWPORT_SIZE.setWidth(window.Width());
    VIEWPORT_SIZE.setHeight(window.Height());
    VIEWPORT_ASPECT_RATIO = VIEWPORT_SIZE.width() / VIEWPORT_SIZE.height();

    QScreen *screen = QApplication::screens().at(0);
    if (screen)
    {
        DPI_X = screen->logicalDotsPerInchX();
        DPI_Y = screen->logicalDotsPerInchY();
        DPI_average = (DPI_X + DPI_Y)/2.f;
        DPI_SQUARE_RATIO = DPI_X/DPI_Y;
        qDebug() << "DPI x y square_aspect viewport_aspect : "
                 << DPI_X << DPI_Y << DPI_SQUARE_RATIO << VIEWPORT_ASPECT_RATIO;
    }
}

QVector2D DPIHelper::VisualSize(float pctOfTotal, float visualRelative, bool horizontal)
{
    QVector2D result;
    if (horizontal)
    {
        float sx = pctOfTotal*VIEWPORT_SIZE.width();
        float sy = sx*visualRelative/DPI_SQUARE_RATIO;
        result = QVector2D(sx, sy);
    }
    else
    {
        float sy = pctOfTotal*VIEWPORT_SIZE.height();
        float sx = sy*visualRelative*DPI_SQUARE_RATIO;
        result = QVector2D(sx, sy);
    }
    return result;
}

QVector2D DPIHelper::FitInto(QVector2D currentSize, QVector2D maxArea)
{
    float fx = maxArea.x()/currentSize.x();
    float fy = maxArea.y()/currentSize.y();
    return ((fx<fy)?fx:fy) * currentSize;;
}
