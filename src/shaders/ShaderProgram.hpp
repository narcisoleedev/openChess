#pragma once

#include <iostream>
#include <glad/glad.h>

class ShaderProgram{
    private:
        int shaderProgram;
    public:
        ShaderProgram(){
            shaderProgram = glCreateProgram();
        };
        void attachShader(unsigned int vertexShader, unsigned int fragmentShader){ 
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
        unsigned int getProgram(){
            return shaderProgram;
        }
};