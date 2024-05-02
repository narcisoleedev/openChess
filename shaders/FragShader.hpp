#include <iostream>
#include <glad/glad.h>

class FragShader{
    private:
        unsigned int fragmentShader;
        const char* fragmentShaderSource = "#version 330 core\n"
                                "in vec3 inColor;\n"
                                "out vec4 FragColor;\n"
                                "void main()\n"
                                "{\n"
                                "   FragColor = vec4(inColor, 1.0);\n"
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
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
            infoLog << std::endl;
            }
            return fragmentShader;
        }
        void deleteShader(){
            glDeleteShader(fragmentShader);
        }
};