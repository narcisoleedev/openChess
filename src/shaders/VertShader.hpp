#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#ifdef _WIN32
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd

#include <glad/glad.h>

using namespace std;

class VertShader{
    private:
        unsigned int vertexShader;
        string vertexShaderString;
        const char* vertexShaderSource;

        int success;
        char infoLog[512];

        string readFile(string filePath){
            char cwd[PATH_MAX];
            if (GetCurrentDir(cwd, sizeof(cwd)) != NULL) {
                std::cout << "Current working directory: " << cwd << std::endl;
            } else {
                perror("getcwd() error");
            }

            ifstream myFile(cwd + filePath);
            if(myFile.is_open()){
                    stringstream buffer;
                    buffer << myFile.rdbuf();
                    myFile.close();
                    return buffer.str();
            } 
            else{
                cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << (cwd+filePath) << endl;
                return "";
                }   
            }

    public:
        VertShader(string filePath){
            vertexShaderString = readFile(filePath);
        }
        unsigned int compileShader(){
            vertexShaderSource = vertexShaderString.c_str();
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
            glCompileShader(vertexShader);
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
            cout << vertexShader << endl;
            return vertexShader;
        }
        void deleteShader(){
            glDeleteShader(vertexShader);
        }
};

#endif