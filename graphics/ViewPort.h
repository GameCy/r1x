#ifndef VIEWPORT_H
#define VIEWPORT_H
#include <QVector2D>
#include "Ogl.h"

struct ViewPort {
    ViewPort()  { X1=Y1=X2=Y2=0; }
    ViewPort(int x1, int y1, int x2, int y2)
    {
        X1 = x1; Y1 = y1; X2 = x2; Y2 = y2;
    }
    void SetLowerPoint(int x1, int y1)
    {
        X1 = x1; Y1 = y1;
    }
    void SetHighPoint(int x2, int y2)
    {
        X2 = x2; Y2 = y2;
    }
    int     Width()  { return X2 - X1; }
    int     Height() { return Y2 - Y1; }
    float   AspectRatio() { return (X2-X1)/(Y2-Y1); }
    QVector2D LocalPos(QVector2D screenPos)
    {
        float x = float(screenPos.x()-X1)/float(X2-X1);
        float y = float(screenPos.y()-Y1)/float(Y2-Y1);
        return QVector2D(x,y);
    }
    void GLApply()
    {
        ogl.glViewport( X1, Y1, X2-X1, Y2-Y1);
    }

    QVector2D Normalized(float x, float y)
    {
        return QVector2D( X1 + x*(X2-X1), Y1 + y*(Y2-Y1) );
    }

    QVector2D Size()
    {
        return QVector2D(X2-X1, Y2-Y1);
    }

    int X1; int Y1; int X2; int Y2;
};

#endif // VIEWPORT_H
