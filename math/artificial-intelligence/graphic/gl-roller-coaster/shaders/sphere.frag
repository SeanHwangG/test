#version 330 core

in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;
uniform bool isNormal = false;
uniform vec3 color = vec3(1, 0, 0);

out vec4 fragColor;

void main()
{
    if (isNormal) {
        fragColor = vec4(Normal, 1.0);
    } else {
        vec3 I = normalize(Position - cameraPos);
        vec3 R = reflect(I, normalize(Normal));
        fragColor = vec4(texture(skybox, R).rgb, 1.0);
    }
}
