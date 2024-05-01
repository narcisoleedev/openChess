#include <iostream>
#include <glad/glad.h>

class VertShader{
    private:
        unsigned int vertexShader;
        const char* vertexShaderSource = "#version 330 core\n"
                                "layout (location=0) in vec3 inPos;\n"
                                "layout (location=1) in vec4 Color;\n"
                                "out vec4 inColor;\n"
                                "void main()\n"
                                "{\n"
                                "   gl_Position = vec4(inPos.x, inPos.y, inPos.z, 1.0);\n"
                                "   inColor = Color;\n"
                                "}\n\0";
    public:
        VertShader(){}
        unsigned int compileShader(){
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
            glCompileShader(vertexShader);
            return vertexShader;
        }
        void deleteShader(){
            glDeleteShader(vertexShader);
        }
};