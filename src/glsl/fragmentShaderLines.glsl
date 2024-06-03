#version 330 core
in vec3 objectColor;
out vec4 FragColor;
uniform vec3 ambientStrength;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
void main()
{
   //Calculate FragColor
   FragColor = vec4(objectColor, 1.0);
};