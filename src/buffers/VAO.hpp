#pragma once 

#include <iostream>
#include <glad/glad.h>

class VAO{
    private:
        unsigned int vao;
    public:
        VAO(){}
        void genVertexArrays(int num){
            glGenVertexArrays(num, &vao);
        }
        void bindVertexArray(){
            glBindVertexArray(vao);
        }
        void unbindVertexArray(){
            glBindVertexArray(0);
        }
        void vertexAttribPointer(int index, int size, GLenum type, bool normalized, int stride, void* pointer){
            glVertexAttribPointer(index, size, type, normalized, stride, pointer);
        }
        void enableVertexArray(int index){
            glEnableVertexAttribArray(index);
        }
        void deleteVertexArrays(){
            glDeleteVertexArrays(1, &vao);
        }
};