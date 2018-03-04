#ifdef GL_ES
#ifdef GL_FRAGMENT_PRECISION_HIGH
   precision highp float;
#else
   precision mediump float;
#endif
#endif

uniform mat4 u_MVPMatrix;      // A constant representing the combined model/view/projection matrix.
uniform mat4 u_MVMatrix;       // A constant representing the combined model/view matrix.

attribute vec4 inputPosition;
attribute vec2 inputTexCoord;
attribute vec4 inputColor;

varying vec3 vertPos;
varying vec2 outTexCoord;
varying vec4 colorInterp;

uniform bool hasColorPerVertex;

void main(){
    gl_Position = u_MVPMatrix * inputPosition;
    vec4 vertPos4 = u_MVMatrix * inputPosition;
    vertPos = vec3(vertPos4) / vertPos4.w;

    outTexCoord = inputTexCoord;
    if (hasColorPerVertex)
    {
        colorInterp = inputColor;
    }
    else
    {
        colorInterp = vec4(1,1,1,1);
    }
}
