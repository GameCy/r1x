uniform mat4 u_MVPMatrix;      // A constant representing the combined model/view/projection matrix.
uniform mat4 u_MVMatrix;       // A constant representing the combined model/view matrix.

attribute vec4 a_Position;     // vertex in
attribute vec2 a_TexCoord;     // UV in
attribute vec3 a_Normal;       // normal in

varying vec3 v_Position;       // out
varying vec2 v_TexCoord;       // out
varying vec3 v_Normal;         // out.


void main()
{
    // Transform the vertex into eye space.
    v_Position = vec3(u_MVMatrix * a_Position);

    // Pass through the color.
    v_TexCoord = a_TexCoord;

    // Transform the normal's orientation into eye space.
    v_Normal = vec3(u_MVMatrix * vec4(a_Normal, 0.0));

    // gl_Position is a special variable used to store the final position.
    // Multiply the vertex by the matrix to get the final point in normalized screen coordinates.
    gl_Position = u_MVPMatrix * a_Position;
}
