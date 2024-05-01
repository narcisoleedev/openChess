#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "./shaders/FragShader.hpp"
#include "./shaders/VertShader.hpp"
#include "./shaders/ShaderProgram.hpp"

using namespace std;

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(600, 600, "Title", NULL, NULL);
    if(window==NULL){
        cerr << "error creating window" << endl;
        return -1;
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cerr << "Failed to initialize GLAD" << endl;
        return -1;
    }
    glViewport(0, 0, 800, 800);

    VertShader vertShader;
    FragShader fragShader;

    ShaderProgram shaderProgram;
    shaderProgram.attachShader(vertShader.compileShader(), fragShader.compileShader());

    vertShader.deleteShader();
    fragShader.deleteShader();
    
    while(!glfwWindowShouldClose(window)){
        shaderProgram.useProgram();
        glfwSwapBuffers(window);
    }

    shaderProgram.deleteProgram();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

