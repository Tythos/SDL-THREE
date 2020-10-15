/*
*/

uniform mat4 uProjection;
uniform mat4 uModelview;

void main() {
    gl_Position = uProjection * uModelview * gl_Vertex;
}
