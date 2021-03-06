#ifndef _PHONGSHADER_HEADER_
#define _PHONGSHADER_HEADER_
#include <QMatrix4x4>
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include "ViewPort.h"

class PhongShader
{
public:
    PhongShader();

    bool    InitShaders();
    void    Destroy();

    bool    Bind();
    void    UseSpecular(bool hasSpecular);

    void    ClearColorMask();
    void    SetColorMask(QVector4D mask);
    void    SetLightPos(QVector3D lightPos);
    void    SetAlphaTesting(float lowerCutOff);

    void    UpdateMatrices(QMatrix4x4 &projection, QMatrix4x4 &model);

    void setColorAmbient(const QVector3D &value);

    void setColorDiffuse(const QVector3D &value);

    void setColorSpecular(const QVector3D &value);

private:
    QOpenGLShaderProgram shaders;
    QVector3D LightPos;
    QVector4D ColorMask;

    QVector3D colorAmbient;
    QVector3D colorDiffuse;
    QVector3D colorSpecular;
};

#endif
