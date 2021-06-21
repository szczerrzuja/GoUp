#version 430 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 3) in vec4 color;

out vec3 Normal;
out vec3 FragPos;
out vec4 objectColor;



uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    lightPos = lightPosition;
    gl_Position = projection * view *  model * vec4(position, 1.0f);
    vec3 lightVector = normalize(lightPosition - position);
    FragPos = vec3(model * vec4(position, 1.0f));
    objectColor = color * dot(lightVector, normal);
    Normal = mat3(transpose(inverse(model))) * normal;
}