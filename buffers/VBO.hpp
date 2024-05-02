#include <iostream>
#include <glad/glad.h>

class VBO{
    private:
        unsigned int vbo;
    public:
        VBO(){}
        void genBuffer(){
            glGenBuffers(1, &vbo);
        }
        void bindBuffer(){
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
        }
        void unbindBuffer(){
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        void bufferData(int sizeofData, GLenum how){
            glBufferData(GL_ARRAY_BUFFER, sizeofData, NULL, how);
        }
        void bufferSubData(int offset, int sizeofData, float* data){
            glBufferSubData(GL_ARRAY_BUFFER, offset, sizeofData, data);
        }
        void deleteBuffers(){
            glDeleteBuffers(1, &vbo);
        }
};