#version 330 core
in vec3 objectColor;
in vec3 verPos;
out vec4 FragColor;
uniform vec3 ambientStrength;
uniform vec3 lightColor;
uniform vec3 lightPos;
void main()
{
    //Compute normal (copied from ChatGPT, not sure if it will work)
    vec3 edge1 = verPos - vec3(0.0, 0.0, 0.0);
    vec3 edge2 = vec3(1.0, 0.0, 0.0) - vec3(0.0, 0.0, 0.0);
    vec3 normal = normalize(cross(edge1, edge2));

   //Calculate diffuseLighting
   vec3 normLightPos = normalize(lightPos);
   float diff = max(dot(normal, lightPos), 0.0);
   vec3 diffuseColor = diff * lightColor;

   //Calculate ambientColor
   vec3 ambientColor = ambientStrength * lightColor;

   //Calculate FragColor
   FragColor = vec4((ambientColor + diffuseColor) * objectColor, 1.0);
}\0;