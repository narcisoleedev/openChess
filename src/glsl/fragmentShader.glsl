#version 330 core
in vec3 localPos;
in vec3 normal;
in vec3 objectColor;
out vec4 FragColor;
uniform vec3 ambientStrength;
uniform vec3 lightColor;
uniform vec3 lightPos;
void main()
{
   //Calculate diffuseLighting
   vec3 normLightPos = normalize(lightPos - localPos);
   float diff = max(dot(normal, lightPos), 0.0);
   vec3 diffuseColor = diff * lightColor;

   //Calculate ambientColor
   vec3 ambientColor = ambientStrength * lightColor;

   //Calculate FragColor
   FragColor = vec4((ambientColor + diffuseColor) * objectColor, 1.0);
};