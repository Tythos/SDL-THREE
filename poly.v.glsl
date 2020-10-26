/*
*/

uniform mat4 uProjection;
uniform mat4 uModelview;
attribute vec3 aPos2D;
attribute vec2 aTexCoord;
varying vec2 vTexCoord;

void main() {
	vTexCoord = aTexCoord;
	gl_Position = uProjection * uModelview * vec4(aPos2D.x, aPos2D.y, 0.0, 1.0);
}
