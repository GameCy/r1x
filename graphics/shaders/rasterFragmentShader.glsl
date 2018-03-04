#ifdef GL_ES
#ifdef GL_FRAGMENT_PRECISION_HIGH
   precision highp float;
#else
   precision mediump float;
#endif
#endif

uniform sampler2D texture;

varying vec3 vertPos;
varying vec2 outTexCoord;
varying vec4 colorInterp;

uniform vec4 colorMask;
uniform float alphaTestLimit;

void main() {
    vec4 tex_color = texture2D(texture, outTexCoord) * colorInterp;
    if (tex_color.a<alphaTestLimit)
        discard;

    gl_FragColor = colorMask * tex_color;
}
