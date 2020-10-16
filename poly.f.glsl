/*
*/

uniform sampler2D uTextureUnit;
varying vec2 vTexCoord;

void main() {
	gl_FragColor = texture(uTextureUnit, vTexCoord);
}
