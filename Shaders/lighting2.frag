#version 430 core

out vec4 color;

in vec3 Normal;
in vec3 vPosition;
in vec4 objectColor;

uniform vec3  lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main()
{
    // Ambient
    vec3 lightVector = normalize(lightPos-vPosition);
    float ambientStrength = 0.45f;
    vec4 ambient = ambientStrength * vec4(lightColor, 1.0f);
    
    // Diffuse
    vec3 norm = normalize(Normal);
    float brightness = dot(norm, lightVector);;
    vec4 diffuse = vec4(brightness, brightness, brightness, 1.0) * (1-ambientStrength );

    //Specular
    float specularStrength = 0.1f;
    vec3 lightDir = lightPos + vec3(1,1,1);
    vec3 viewDir = normalize(viewPos - vPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = dot(viewDir, reflectDir);
    spec = pow(spec, 50);
    vec4 specularLight = vec4(spec, 0,0,1);
    

    color =(ambient +clamp(diffuse,0,1)+specularLight ) * objectColor;

}

#version 430 core
struct Light
{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    
    float constant;
    float linear;
    float quadratic;
    //colory
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct Material
{
    vec3 diffuse;
    vec3 specular;
    float     shininess;
};
out vec4 color;

in vec3 Normal;
in vec3 vPosition;
in vec4 objectColor;

uniform Light light;
uniform Material mat;
uniform vec3 viewPos;

void main()
{
    // Ambient - light.ambient
    vec3 lightVector = normalize(lightPos-vPosition);
    
    // Diffuse
    vec3 norm = normalize(Normal);
    float brightness = dot(norm, lightVector);
    vec3 lightdir = normalize(light.position - vPosition);
    vec3 diffuse = vec3(brightness, brightness, brightness) * light.diffuse;

    //Specular
    float specularStrength = 0.1f;
    vec3 viewDir = normalize(viewPos - vPosition);
    vec3 reflectDir = reflect(-light.direction, norm);
    float spec = dot(viewDir, reflectDir);
    spec = pow(spec, 50);
    vec4 specularLight = vec4(spec, 0,0,1);
    

    color = vec4((ambient +clamp(diffuse,0,1)+specularLight ), 1.0f) * objectColor;

}
