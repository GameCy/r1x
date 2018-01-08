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
varying vec3 normalInterp;

uniform vec3 lightPos;
uniform vec4 colorMask;
uniform float alphaTestLimit;

uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;

uniform bool hasLighting;
uniform bool useSpecular;

void main() {
    vec4 tex_color = texture2D(texture, outTexCoord);
    if (tex_color.a<alphaTestLimit)
        discard;

    if (!hasLighting)
    {
        gl_FragColor = colorMask * tex_color;

    }
    else
    {
        vec3 normal = normalize(normalInterp);
        vec3 lightDir = normalize(lightPos - vertPos);
        vec3 reflectDir = reflect(-lightDir, normal);
        vec3 viewDir = normalize(-vertPos);

        // attenuation
        float d = length(lightPos - vertPos);
        float attenuation = min(1.0, (1.0 / (0.25 + 0.015*d)) );

        float lambertian = max(dot(lightDir,normal), 0.0);
        vec3 finalFragment = ambientColor + vec3(attenuation*lambertian*tex_color);
        if (useSpecular && (lambertian > 0.0) )
        {
            float specAngle = max(dot(reflectDir, viewDir), 0.0);
            finalFragment += attenuation*pow(specAngle, 8.0)*specularColor;
        }

        gl_FragColor = vec4( finalFragment , tex_color.a) * colorMask;
    }
}
