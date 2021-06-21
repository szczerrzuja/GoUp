#version 430 core
out vec4 color;
struct Light
{
vec3 position;
vec3 direction;
vec3 Color;

float cutOff;
float outerCutOff;
float constant;
float linear;
float quadratic;

};
in vec3 Normal;
in vec3 vPosition;
in vec4 objectColor;


uniform vec3 viewPos;
uniform Light light;

void main()
{
    // Ambient
    vec3 lightVector = normalize(light.position-vPosition);
    float ambientStrength = 0.05f;
    vec4 ambient = ambientStrength * vec4(light.Color,1.0f);
    
    // Diffuse
    vec3 norm = normalize(Normal);
    float diff = clamp(abs(dot(lightVector, norm)), 0,1);
    vec4 diffuse = vec4(diff, diff, diff, 1.0f) * vec4(light.Color, 1.0f)*1.0;

    //Specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - vPosition);
    vec3 reflectDir = reflect(-lightVector, norm);
    float spec = clamp(abs(dot(reflectDir, viewDir)), 0, 1) ;
    spec = spec*spec;
    vec4 specular =vec4(spec, spec, spec, 1.0f)* specularStrength  * vec4(light.Color, 1.0f);
    //spotlight
   
    float theta = dot(lightVector, normalize(-light.direction));
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse  *= intensity;
    specular *= intensity;
    // Attenuation
     /*
    float distance    = length(light.position - vPosition);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    */


    color =  (ambient + diffuse + specular) * objectColor;
}
