#include <iostream>
#include <glad/glad.h>

class FragShader{
    private:
        unsigned int fragmentShader;
        const char* fragmentShaderSource = 
            "#version 330 core\n"
            "in vec3 localPos;\n"
            "in vec3 normal;\n"
            "in vec3 objectColor;\n"
            "out vec4 FragColor;\n"
            "uniform vec3 ambientStrength;\n"
            "uniform vec3 lightColor;\n"
            "uniform vec3 lightPos;\n"
            "uniform vec3 viewPos;\n"
            "void main()\n"
            "{\n"
            "   //Calculate diffuseLighting\n"
            "   vec3 normLightPos = normalize(lightPos - localPos);\n"
            "   float diff = max(dot(normal, lightPos), 0.0);\n"
            "   vec3 diffuseColor = diff * lightColor;\n"
            "\n"
            "   //Calculate specularLighting\n"
            "   float specularStrength = 1.0;\n"
            "   vec3 viewDir = normalize(viewPos - localPos);\n"
            "   vec3 reflectDir = reflect(-normLightPos, normal);\n"
            "   float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);\n"
            "   vec3 specular = specularStrength * spec * lightColor;\n"
            "\n"
            "   //Calculate ambientColor\n"
            "   vec3 ambientColor = ambientStrength * lightColor;\n"
            "\n"
            "   //Calculate FragColor\n"
            "   FragColor = vec4((ambientColor + diffuseColor + specular) * objectColor, 1.0);\n"
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