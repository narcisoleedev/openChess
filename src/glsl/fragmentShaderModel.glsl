#version 330 core
in vec3 localPos;
in vec3 normal;
in vec2 objectText;
out vec4 FragColor;
uniform vec3 ambientStrength;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

struct Material {
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

void main()
{
   //Calculate diffuseLighting
   vec3 normLightPos = normalize(lightPos - localPos);
   float diff = max(dot(normal, normLightPos), 0.0);
   vec3 diffuseColor = diff * lightColor * vec3(texture(material.diffuse, objectText));

   //Calculate specularLighting
   vec3 viewDir = normalize(viewPos - localPos);
   vec3 reflectDir = reflect(-normLightPos, normal);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   vec3 specular = (material.specular * spec) * lightColor;

   //Calculate ambientColor
   vec3 ambientColor = ambientStrength * lightColor;

   //Calculate FragColor
   FragColor = vec4((ambientColor + diffuseColor + specular) * objectColor, 1.0);
};