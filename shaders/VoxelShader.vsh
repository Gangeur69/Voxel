#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoordsIn;
layout(location = 2) in vec3 normal;

out vec3 worldNormal;
out vec2 textureCoords;

uniform mat4 projection;
uniform mat4 camera;

void main()
{
  worldNormal = normal;
  textureCoords = textureCoordsIn;
  gl_Position = projection * camera * vec4(position, 1.0);
}
