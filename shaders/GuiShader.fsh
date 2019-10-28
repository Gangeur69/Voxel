#version 330 core

in vec2 textureCoords;

uniform sampler2D texture;

uniform vec3 color;

void main()
{
  gl_FragColor = vec4(color, 1.0)*texture2D(texture, textureCoords);
}
