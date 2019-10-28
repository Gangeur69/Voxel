#version 330 core

in vec3 worldNormal;
in vec2 textureCoords;

uniform sampler2D texture;
uniform vec3 sunDirection;
uniform vec3 sunColor;

void main()
{
  vec3 uWorldNormal = normalize(worldNormal);
  float intensity = -dot(uWorldNormal, sunDirection);
  intensity = max(0.3, intensity);

  gl_FragColor = intensity * vec4(sunColor, 1.0) * texture2D(texture, textureCoords);
}
