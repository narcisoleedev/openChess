#pragma once 

#include <iostream>
#include <glad/glad.h>

class EBO{
    private:
        unsigned int ebo;
    public:
        EBO(){}
        void genBuffer(){
            glGenBuffers(1, &ebo);
        }
        void bindBuffer(){
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        }
        void unbindBuffer(){
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
        void bufferData(int sizeofData, int* data, GLenum how){
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeofData, data, how);
        }
        /*void bufferSubData(int offset, int sizeofData, float* data){
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, sizeof(data), data);
        }*/
        void deleteBuffers(){
            glDeleteBuffers(1, &ebo);
        }
};