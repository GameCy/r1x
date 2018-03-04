#include "PhongShader.h"
//#include <math.h>


PhongShader::PhongShader()
    : colorAmbient(.1f, .1f, .1f)
    , colorDiffuse(.7f, .7f, .7f)
    , colorSpecular(.2f,.2f, .2f)
{
}

bool PhongShader::InitShaders()
{
    // Compile vertex shader
    if ( (!shaders.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/phongVertexShader.glsl")) ||
         (!shaders.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/phongFragmentShader.glsl")) ||
         (!shaders.link())
         )
        return false;

    // define order of attributes to fix mixup on android
    shaders.bindAttributeLocation("inputPosition", 0);
    shaders.bindAttributeLocation("inputTexCoord", 1);
    shaders.bindAttributeLocation("inputNormal", 2);

    // Bind shader pipeline for use
    if (!shaders.bind())
        return false;

    shaders.setUniformValue("texture", 0); // Use texture unit 0
    shaders.setUniformValue("ambientColor", colorAmbient);
    shaders.setUniformValue("specularColor", colorSpecular);
    shaders.setUniformValue("diffuseColor", colorDiffuse);
    shaders.setUniformValue("useSpecular", false);
    ColorMask = QVector4D(1,1,1,1);
    SetColorMask( ColorMask );
    SetAlphaTesting(0.005f);
    return true;
}

void PhongShader::Destroy()
{
    shaders.release();
    shaders.removeAllShaders();
}

bool PhongShader::Bind()
{
    return shaders.bind();
}

void PhongShader::UseSpecular(bool hasSpecular)
{
    shaders.setUniformValue("useSpecular", hasSpecular);
}

void PhongShader::ClearColorMask()
{
    ColorMask = QVector4D(1,1,1,1);
    shaders.setUniformValue("colorMask", ColorMask);
}

void PhongShader::SetColorMask(QVector4D mask)
{
    ColorMask = mask;
    shaders.setUniformValue("colorMask", mask);
}

void PhongShader::SetLightPos(QVector3D lightPos)
{
    LightPos = lightPos;
    shaders.setUniformValue("lightPos", LightPos);
}

void PhongShader::SetAlphaTesting(float lowerCutOff)
{
    shaders.setUniformValue("alphaTestLimit", lowerCutOff);
}

void PhongShader::UpdateMatrices(QMatrix4x4 &projection, QMatrix4x4 &model)
{
    shaders.setUniformValue("u_MVPMatrix", projection * model);
    shaders.setUniformValue("u_MVMatrix", model);
    shaders.setUniformValue("u_NormalMatrix", model.inverted().transposed());
}

void PhongShader::setColorAmbient(const QVector3D &value)
{
    colorAmbient = value;
    shaders.setUniformValue("ambientColor", colorAmbient);
}

void PhongShader::setColorDiffuse(const QVector3D &value)
{
    colorDiffuse = value;
    shaders.setUniformValue("diffuseColor", colorDiffuse);
}

void PhongShader::setColorSpecular(const QVector3D &value)
{
    colorSpecular = value;
    shaders.setUniformValue("specularColor", colorSpecular);
}
