#version 330 core

const int MAX_JOINTS = 100;
const int MAX_WEIGHTS = 3;

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoordsIn;
layout(location = 2) in vec3 normal;
layout(location = 3) in ivec3 jointIds;
layout(location = 4) in vec3 weights;

uniform mat4 projection;
uniform mat4 camera;
uniform mat4 transformation;
uniform mat4 joints[MAX_JOINTS];

out vec2 textureCoords;
out vec3 worldNormal;

void main()
{
  vec4 localPosition = vec4(0,0,0,0);
  vec4 localNormal = vec4(0,0,0,0);
  for(int i=0;i<MAX_WEIGHTS;i++)
  {
    mat4 joint = joints[jointIds[i]];
    vec4 localJointPosition = joint*vec4(position, 1.0);
    localPosition+=localJointPosition*weights[i];

    vec4 localJointNormal = joint*vec4(normal, 0.0);
    localNormal+=localJointNormal*weights[i];
  }

  worldNormal = (transformation*localNormal).xyz;
  vec4 worldPosition = transformation * localPosition;

  textureCoords = textureCoordsIn;
  gl_Position = projection * camera * worldPosition;
}
