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

class FragShader{
    private:
        unsigned int fragmentShader;
        string fragmentShaderString;
        const char* fragmentShaderSource;

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
        FragShader(string filePath){
            fragmentShaderString = readFile(filePath);
        }
        unsigned int compileShader(){
            fragmentShaderSource = fragmentShaderString.c_str();
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
            glCompileShader(fragmentShader);
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
            cout << fragmentShader << endl;
            return fragmentShader;
        }
        void deleteShader(){
            glDeleteShader(fragmentShader);
        }
};

#endif