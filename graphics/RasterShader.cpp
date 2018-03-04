#include "RasterShader.h"
//#include <math.h>


RasterShader::RasterShader()
{
}

bool RasterShader::InitShaders()
{
    // Compile vertex shader
    if ( (!shaders.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/rasterVertexShader.glsl")) ||
         (!shaders.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/rasterFragmentShader.glsl")) ||
         (!shaders.link())
         )
        return false;

    // define order of attributes to fix mixup on android
    shaders.bindAttributeLocation("inputPosition", 0);
    shaders.bindAttributeLocation("inputTexCoord", 1);
    shaders.bindAttributeLocation("inputColor", 2);

    // Bind shader pipeline for use
    if (!shaders.bind())
        return false;

    shaders.setUniformValue("texture", 0); // Use texture unit 0
    shaders.setUniformValue("hasColorPerVertex", false);
    ColorMask = QVector4D(1,1,1,1);
    SetColorMask( ColorMask );
    SetAlphaTesting(0.005f);
    return true;
}

void RasterShader::Destroy()
{
    shaders.release();
    shaders.removeAllShaders();
}

void RasterShader::UseColorPerVertex(bool colorPerVertex)
{
    shaders.setUniformValue("hasColorPerVertex", colorPerVertex);
}

void RasterShader::UpdateViewport(ViewPort viewport)
{
    QMatrix4x4 modelMatrix;
    QMatrix4x4 ortho;
    ortho.ortho(viewport.X1, viewport.X2, viewport.Y1, viewport.Y2, 0, 256);
    shaders.setUniformValue("u_MVPMatrix", ortho * modelMatrix );
    shaders.setUniformValue("u_MVMatrix", modelMatrix);
}

bool RasterShader::Bind()
{
    return shaders.bind();
}

void RasterShader::ClearColorMask()
{
    ColorMask = QVector4D(1,1,1,1);
    shaders.setUniformValue("colorMask", ColorMask);
}

void RasterShader::SetColorMask(QVector4D mask)
{
    ColorMask = mask;
    shaders.setUniformValue("colorMask", mask);
}

void RasterShader::SetAlphaTesting(float lowerCutOff)
{
    shaders.setUniformValue("alphaTestLimit", lowerCutOff);
}
