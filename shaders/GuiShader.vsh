#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 textureCoordsIn;

out vec2 textureCoords;

uniform vec2 location;
uniform vec2 size;

vec2 transform(vec2 pos)
{
  return vec2(location.x + pos.x*size.x, -location.y + pos.y*size.y);
}

void main()
{
  textureCoords = textureCoordsIn;
  gl_Position = vec4(transform(position), -1.0, 1.0);
}
