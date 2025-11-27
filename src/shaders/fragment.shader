#version 330 core

uniform vec3 sphereColor;
uniform vec3 ambientColor;
uniform vec3 difLightPos;
uniform vec3 difLightCol; 
uniform vec3 specLightCol;
uniform vec3 camPos;

in vec3 FragPos;
in vec3 fNormal;

out vec4 fColor;

void main()
{
    // Ambient
    vec3 ambient = 0.3*ambientColor;

    // Diffuse
    vec3 norm = normalize(fNormal);
    vec3 lightDir = normalize(difLightPos - FragPos);
    float diff = dot(norm, lightDir);
    vec3 diffuse = diff * difLightCol;
    
    //Specular
    vec3 viewDir = normalize(camPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, fNormal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0);
    vec3 specular = 2.0 * spec * specLightCol;

    // Final color
    vec3 result=(diffuse+ambient+specular) * sphereColor;
    fColor = vec4(result, 1.0);
}
