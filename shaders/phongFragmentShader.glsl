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
const vec3 ambientColor = vec3(0.1, 0.1, 0.1);
const vec3 diffuseColor = vec3(0.3, 0.3, 0.3);
const vec3 specColor = vec3(0.6, 0.6, 0.6);

void main() {
    vec4 tex_color = texture2D(texture, outTexCoord);
    if (tex_color.a<0.01)
        discard;

    vec3 normal = normalize(normalInterp);
    vec3 lightDir = normalize(lightPos - vertPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 viewDir = normalize(-vertPos);

    float lambertian = max(dot(lightDir,normal), 0.0);
    float specular = 0.0;

    if(lambertian > 0.0) {
       float specAngle = max(dot(reflectDir, viewDir), 0.0);
       specular = pow(specAngle, 8.0);
    }

    // attenuation
    float d = length(lightPos - vertPos);
    float attenuation = min(1.0, (1.0 / (0.25 + 0.015*d)) );

    gl_FragColor = vec4( ambientColor + vec3(attenuation*lambertian*tex_color) + attenuation*specular*specColor , tex_color.a);

}
