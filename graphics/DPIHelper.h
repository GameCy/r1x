#ifndef DPIHELPER_H
#define DPIHELPER_H
#include "ViewPort.h"

#include <QSize>

class DPIHelper
{
public:
    float DPI_X, DPI_Y, DPI_average, DPI_SQUARE_RATIO;
    float VIEWPORT_ASPECT_RATIO;
    QSizeF VIEWPORT_SIZE;

    void Update(ViewPort window);

    QVector2D VisualSize(float pctOfTotal, float visualRelative, bool horizontal=true);
    QVector2D FitInto(QVector2D currentSize, QVector2D maxArea);
};

#endif // DPIHELPER_H
