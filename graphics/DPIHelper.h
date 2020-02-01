#ifndef DPIHELPER_H
#define DPIHELPER_H
#include "ViewPort.h"

class DPIHelper
{
public:
    float DPI_X, DPI_Y, DPI_average;
    float ASPECT_RATIO;

    void Update();
    void UpdateWindowed(ViewPort window);
};

#endif // DPIHELPER_H
