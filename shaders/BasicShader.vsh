#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoordsIn;
layout(location = 2) in vec3 normal;

out vec3 worldNormal;
out vec2 textureCoords;

uniform mat4 projection;
uniform mat4 camera;
uniform mat4 transformation;

void main()
{
  worldNormal = (transformation*vec4(normal,0.0)).xyz;
  textureCoords = textureCoordsIn;
  gl_Position = projection * camera * transformation * vec4(position, 1.0);
}
