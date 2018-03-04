#ifndef _RASTERSHADER_HEADER_
#define _RASTERSHADER_HEADER_
#include <QMatrix4x4>
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include "ViewPort.h"

class RasterShader
{
public:
    RasterShader();

    bool    InitShaders();
    void    Destroy();
    void    UpdateViewport(ViewPort viewport);
    bool    Bind();

    void    UseColorPerVertex(bool colorPerVertex);

    void    ClearColorMask();
    void    SetColorMask(QVector4D mask);
    void    SetAlphaTesting(float lowerCutOff);

private:
    QOpenGLShaderProgram shaders;
    QVector4D ColorMask;
};

#endif
