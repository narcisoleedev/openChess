#include <iostream>
#include <glad/glad.h>

class VertShader{
    private:
        unsigned int vertexShader;
        const char* vertexShaderSource = 
            "#version 330 core\n"
            "layout (location=0) in vec3 inPos;\n"
            "layout (location=1) in vec3 inNormal;\n"
            "layout (location=2) in vec3 inColor;\n"
            "out vec3 localPos;\n"
            "out vec3 normal;\n"
            "out vec3 objectColor;\n"
            "uniform mat4 model;\n"
            "uniform mat4 view;\n"
            "uniform mat4 projection;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = projection * view * model * vec4(inPos, 1.0);\n"
            "   localPos = vec3(model * vec4(inPos, 1.0));\n"
            "   normal = mat3(transpose(inverse(model))) * inNormal;\n"
            "   objectColor = inColor;\n"
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