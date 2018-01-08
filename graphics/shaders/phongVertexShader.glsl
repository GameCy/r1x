#ifdef GL_ES
#ifdef GL_FRAGMENT_PRECISION_HIGH
   precision highp float;
#else
   precision mediump float;
#endif
#endif

uniform mat4 u_MVPMatrix;      // A constant representing the combined model/view/projection matrix.
uniform mat4 u_MVMatrix;       // A constant representing the combined model/view matrix.
uniform mat4 u_NormalMatrix;

attribute vec4 inputPosition;
attribute vec2 inputTexCoord;
attribute vec3 inputNormal;


varying vec3 vertPos;
varying vec2 outTexCoord;
varying vec3 normalInterp;

uniform bool isParticle;

void main(){
    gl_Position = u_MVPMatrix * inputPosition;
    vec4 vertPos4 = u_MVMatrix * inputPosition;
    vertPos = vec3(vertPos4) / vertPos4.w;

    outTexCoord = inputTexCoord;
    if (isParticle)
    {
        normalInterp = vec3(0.0, 0.0, 1.0);
    }
    else
    {
        normalInterp = vec3(u_NormalMatrix * vec4(inputNormal, 0.0));
    }
}
