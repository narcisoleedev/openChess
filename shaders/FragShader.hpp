#include <iostream>
#include <glad/glad.h>

class FragShader{
    private:
        unsigned int fragmentShader;
        const char* fragmentShaderSource = "#version 330 core\n"
                                "in vec4 InColor;\n"
                                "out vec4 FragColor;\n"
                                "void main()\n"
                                "{\n"
                                "   FragColor = InColor;\n"
                                "}\n\0";
    public:
        FragShader(){}
        unsigned int compileShader(){
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader,1, &fragmentShaderSource, NULL);
            glCompileShader(fragmentShader);
            return fragmentShader;
        }
        void deleteShader(){
            glDeleteShader(fragmentShader);
        }
};