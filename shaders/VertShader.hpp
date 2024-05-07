#include <iostream>
#include <glad/glad.h>

class VertShader{
    private:
        unsigned int vertexShader;
        const char* vertexShaderSource = "#version 330 core\n"
                                "layout (location=0) in vec3 inPos;\n"
                                "layout (location=1) in vec3 Color;\n"
                                "out vec3 inColor;\n"
                                "uniform mat4 transform;\n"
                                "void main()\n"
                                "{\n"
                                "   gl_Position = transform * vec4(inPos.x, inPos.y, inPos.z, 1.0);\n"
                                "   inColor = Color;\n"
                                "}\n\0";
        int success;
        char infoLog[512];
    public:
        VertShader(){}
        unsigned int compileShader(){
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
            glCompileShader(vertexShader);
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
            infoLog << std::endl;
            }
            return vertexShader;
        }
        void deleteShader(){
            glDeleteShader(vertexShader);
        }
};