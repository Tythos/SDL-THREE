/*
*/

uniform mat4 uProjection;
uniform mat4 uModelview;
attribute vec2 aPos2D;
attribute vec3 aMultiColor;
varying vec4 vMultiColor;

void main() {
    vMultiColor = vec4(aMultiColor, 1.0);
    gl_Position = uProjection * uModelview * vec4(aPos2D.x, aPos2D.y, 0.0, 1.0);
}
