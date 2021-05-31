#version 330 core
// This is a sample fragment shader.

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note that you do not have access to the vertex shader's default output, gl_Position.
in vec3 FragPos;
in vec3 Normal;

uniform mat4 model;
uniform vec3 color;
uniform vec3 viewPos;
uniform bool isNormal = false;

// ambient
uniform vec3 ambiK = vec3(0.2,0.2,0.2);
uniform vec3 diffK = vec3(1,1,1);
uniform vec3 specK = vec3(1,1,1);
uniform float shinK = 10;

struct PointLight {
  vec3 pos;
  vec3 color;
};

uniform PointLight pl;

vec3 CalcPointLight(PointLight light, vec3 norm, vec3 viewDir) {
  float distance = length(light.pos - FragPos);
  float attenuation = 1.0 / distance;
  // ambient
  vec3 ambient = light.color * ambiK * attenuation;

  // diffuse
  //vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(light.pos - FragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * diffK * light.color;

  // specular
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), shinK);
  vec3 specular = specK * spec * 0.5 * light.color;

  // Use the color passed in. An alpha of 1.0f means it is not transparent.
  return (ambient + diffuse + specular) * color * attenuation * 7;
}

// You can output many things. The first vec4 type output determines the color of the fragment
out vec4 fragColor;

void main() {
  mat3 normalMatrix = transpose(inverse(mat3(model)));
  vec3 norm = normalize(normalMatrix * Normal);
  vec3 viewDir = normalize(viewPos - FragPos);

  if (isNormal) {
      fragColor = vec4(Normal, 1);
  }
  else {// Use the color passed in. An alpha of 1.0f means it is not transparent.
      fragColor = vec4(CalcPointLight(pl, norm, viewDir), 1);
  }
}
