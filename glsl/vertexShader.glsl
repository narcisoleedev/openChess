#version 330 core
layout (location=0) in vec3 inPos;
layout (location=1) in vec3 inNormal;
layout (location=2) in vec3 inColor;
out vec3 localPos;
out vec3 normal;
out vec3 objectColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
   gl_Position = projection * view * model * vec4(inPos, 1.0);
   localPos = model * vec4(inPos, 1.0);
   objectColor = inColor;
};