#include "Shader.h"
//#include <math.h>


Shader::Shader()
    : colorAmbient(.1f, .1f, .1f)
    , colorDiffuse(.7f, .7f, .7f)
    , colorSpecular(.2f,.2f, .2f)
{
}

bool Shader::InitShaders()
{
    // Compile vertex shader
    if ( (!phongShaders.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/phongVertexShader.glsl")) ||
         (!phongShaders.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/phongFragmentShader.glsl")) ||
         (!phongShaders.link())
         )
        return false;

    // define order of attributes to fix mixup on android
    phongShaders.bindAttributeLocation("inputPosition", 0);
    phongShaders.bindAttributeLocation("inputTexCoord", 1);
    phongShaders.bindAttributeLocation("inputNormal", 2);

    // Bind shader pipeline for use
    if (!phongShaders.bind())
        return false;

    phongShaders.setUniformValue("texture", 0); // Use texture unit 0
    phongShaders.setUniformValue("ambientColor", colorAmbient);
    phongShaders.setUniformValue("specularColor", colorSpecular);
    phongShaders.setUniformValue("diffuseColor", colorDiffuse);
    phongShaders.setUniformValue("useSpecular", false);
    ColorMask = QVector4D(1,1,1,1);
    SetColorMask( ColorMask );
    SetAlphaTesting(0.005f);
    return true;
}

void Shader::Destroy()
{
    phongShaders.release();
    phongShaders.removeAllShaders();
}

void Shader::ParticleRenderingMode(bool on)
{
    phongShaders.setUniformValue("isParticle", on);
    phongShaders.setUniformValue("hasLighting", !on);
}

void Shader::UseSpecular(bool hasSpecular)
{
    phongShaders.setUniformValue("useSpecular", hasSpecular);
}

void Shader::RasterMode(float width, float height)
{
    phongShaders.setUniformValue("isParticle", true);
    phongShaders.setUniformValue("hasLighting", false);

    QMatrix4x4 modelMatrix;
    QMatrix4x4 ortho;
    ortho.ortho(0, width, 0, height, 0, 256);
    phongShaders.setUniformValue("u_MVPMatrix", ortho * modelMatrix );
    phongShaders.setUniformValue("u_MVMatrix", modelMatrix);
    phongShaders.setUniformValue("u_NormalMatrix", modelMatrix.inverted().transposed());
}

void Shader::ClearColorMask()
{
    ColorMask = QVector4D(1,1,1,1);
    phongShaders.setUniformValue("colorMask", ColorMask);
}

void Shader::SetColorMask(QVector4D mask)
{
    ColorMask = mask;
    phongShaders.setUniformValue("colorMask", mask);
}

void Shader::SetLightPos(QVector3D lightPos)
{
    LightPos = lightPos;
    phongShaders.setUniformValue("lightPos", LightPos);
}

void Shader::SetAlphaTesting(float lowerCutOff)
{
    phongShaders.setUniformValue("alphaTestLimit", lowerCutOff);
}

void Shader::UpdateMatrices(QMatrix4x4 &projection, QMatrix4x4 &model)
{
    phongShaders.setUniformValue("u_MVPMatrix", projection * model);
    phongShaders.setUniformValue("u_MVMatrix", model);
    phongShaders.setUniformValue("u_NormalMatrix", model.inverted().transposed());
}

void Shader::setColorAmbient(const QVector3D &value)
{
    colorAmbient = value;
    phongShaders.setUniformValue("ambientColor", colorAmbient);
}

void Shader::setColorDiffuse(const QVector3D &value)
{
    colorDiffuse = value;
    phongShaders.setUniformValue("diffuseColor", colorDiffuse);
}

void Shader::setColorSpecular(const QVector3D &value)
{
    colorSpecular = value;
    phongShaders.setUniformValue("specularColor", colorSpecular);
}
