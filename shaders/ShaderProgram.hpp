#include <iostream>
#include <glad/glad.h>

class ShaderProgram{
    private:
        int shaderProgram;
    public:
        ShaderProgram(){};
        void attachShader(unsigned int vertexShader, unsigned int fragmentShader){ 
            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);
        }; 
        void useProgram(){
            glUseProgram(shaderProgram);
        }
        void deleteProgram(){
            glDeleteProgram(shaderProgram);
        }
};