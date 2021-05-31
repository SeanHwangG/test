#version 330 core
// This is a sample fragment shader.

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note that you do not have access to the vertex shader's default output, gl_Position.
in vec3 FragPos;
in vec3 Normal;

uniform mat4 model;
uniform vec3 objectColor;
uniform vec3 viewPos;

// ambient
uniform vec3 ambiK;
uniform vec3 diffK;
uniform vec3 specK;
uniform float shinK;

uniform bool isNormal;

struct PointLight {
  vec3 pos;
  vec3 color;
  bool on;
};
struct DirLight {
  vec3 dir;
  vec3 color;
  bool on;
};
struct SpotLight {
  vec3 dir;
  vec3 color;
  float beamWidth;
  float taper;
  bool on;
};

uniform PointLight pl;
uniform DirLight dl;
uniform SpotLight sl;


// You can output many things. The first vec4 type output determines the color of the fragment
out vec4 fragColor;

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
  return (ambient + diffuse + specular) * objectColor * attenuation * 40;
}

vec3 CalcDirLight(DirLight light, vec3 norm, vec3 viewDir) {
  vec3 lightDir = normalize(-light.dir);
  vec3 reflectDir = reflect(-light.dir, norm);

  float diff = max(dot(norm, light.dir), 0.0);
  // Specular shading
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), shinK);

  vec3 ambient = ambiK;
  vec3 diffuse = diffK * diff;
  vec3 specular = specK * spec;

  return (ambient + diffuse + specular) * objectColor;
}

vec3 CalcSpotLight(SpotLight light, vec3 norm, vec3 viewDir) {
  //light.beamWidth;

  vec3 lightDir = normalize(-light.dir);
  vec3 reflectDir = reflect(-light.dir, norm);
  vec3 recieveDir = normalize(light.dir - FragPos);

  float diff = max(dot(norm, light.dir), 0.0);
  // Specular shading
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), shinK);
  vec3 ambient = ambiK;
  vec3 diffuse = diffK * diff;
  vec3 specular = specK * spec;

  if (-dot(lightDir, recieveDir) < 0.8) {
      return vec3(0, 0, 0);
  }

  return (ambient + diffuse + specular) * 3 * pow(-dot(lightDir, recieveDir), 15) * objectColor;
}

void main() {
  mat3 normalMatrix = transpose(inverse(mat3(model)));
  vec3 norm = normalize(normalMatrix * Normal);
  vec3 viewDir = normalize(viewPos - FragPos);

  vec3 result;

  if (isNormal) {
    fragColor = vec4(Normal, 1);
  } else {
    if (dl.on) result += CalcDirLight(dl, norm, viewDir);
    if (pl.on) result += CalcPointLight(pl, norm, viewDir);
    if (sl.on) result += CalcSpotLight(sl, norm, viewDir);

    fragColor = vec4(result, 1);
  }
}
