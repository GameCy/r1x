//precision mediump float;

uniform vec3 u_CamPos;       // The position of the light in eye space.
uniform vec3 u_LightPos;       // The position of the light in eye space.
uniform sampler2D texture;

varying vec3 v_Position;       // Interpolated position for this fragment.
varying vec2 v_TexCoord;
varying vec3 v_Normal;         // Interpolated normal for this fragment.


// The entry point for our fragment shader.
void main()
{
    // Will be used for attenuation.
    float distance = length(u_LightPos - v_Position);

    // Get a lighting direction vector from the light to the vertex.
    vec3 lightVector = normalize(u_LightPos - v_Position);

    // Calculate the dot product of the light vector and vertex normal. If the normal and light vector are
    // pointing in the same direction then it will get max illumination.
    float diffuse = max(dot(v_Normal, lightVector), 0.1);
    // Add attenuation.
    //diffuse = diffuse * (1.0 / (1.0 + (0.0025 * distance)));

    vec3 N = normalize(v_Normal);
    float lambertTerm = dot(N, lightVector);

    float specular = 0;
    if(lambertTerm > 0.0)
    {
        //final_color += gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse * lambertTerm * att;
        diffuse = diffuse*lambertTerm;

        vec3 E = normalize(u_CamPos - v_Position);
        vec3 R = reflect(-lightVector, N);

        specular = pow( max(dot(R, E), 0.0), 8); //gl_FrontMaterial.shininess );

        //final_color += gl_LightSource[0].specular * gl_FrontMaterial.specular * specular * att;
    }


    // Multiply the texel color by the diffuse illumination level to get output color.
    gl_FragColor = texture2D(texture, v_TexCoord)*(0.2+diffuse+specular);
}
