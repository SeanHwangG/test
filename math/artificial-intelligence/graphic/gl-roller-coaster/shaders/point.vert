#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in int idx;

uniform mat4 projection;
uniform mat4 view;
uniform int current;

out vec3 Color;

void main()
{
    gl_Position = projection * view * vec4(position, 1.0);
    
    if (idx == current) {
        Color = vec3(1, 1, 1);
    } else {
        Color = vec3(current, current, 1);
    }
    /*
    else if (idx % 3 == 0) {
        Color = vec3(1, 0, 0);
    }
    else {
        Color = vec3(0, 1, 0);
    }*/
}
