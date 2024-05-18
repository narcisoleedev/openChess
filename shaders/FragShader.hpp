#include <iostream>
#include <glad/glad.h>

class FragShader{
    private:
        unsigned int fragmentShader;
        const char* fragmentShaderSource = 
            "#version 330 core\n"
            "in vec3 objectColor;\n"
            "in vec3 verPos;\n"
            "out vec4 FragColor;\n"
            "uniform vec3 ambientStrength;\n"
            "uniform vec3 lightColor;\n"
            "uniform vec3 lightPos;\n"
            "void main()\n"
            "{\n"
            "    //Compute normal (copied from ChatGPT, not sure if it will work)\n"
            "    vec3 edge1 = verPos - vec3(0.0, 0.0, 0.0);\n"
            "    vec3 edge2 = vec3(1.0, 0.0, 0.0) - vec3(0.0, 0.0, 0.0);\n"
            "    vec3 normal = normalize(cross(edge1, edge2));\n"
            "\n"
            "   //Calculate diffuseLighting\n"
            "   vec3 normLightPos = normalize(lightPos);\n"
            "   float diff = max(dot(normal, lightPos), 0.0);\n"
            "   vec3 diffuseColor = diff * lightColor;\n"
            "\n"
            "   //Calculate ambientColor\n"
            "   vec3 ambientColor = ambientStrength * lightColor;\n"
            "\n"
            "   //Calculate FragColor\n"
            "   FragColor = vec4((ambientColor + diffuseColor) * objectColor, 1.0);\n"
            "}\n\0";

        int success;
        char infoLog[512];
    public:
        FragShader(){}
        unsigned int compileShader(){
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader,1, &fragmentShaderSource, NULL);
            glCompileShader(fragmentShader);
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
            infoLog << std::endl;
            }
            return fragmentShader;
        }
        void deleteShader(){
            glDeleteShader(fragmentShader);
        }
};