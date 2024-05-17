#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unistd.h>

#include "./shaders/FragShader.hpp"
#include "./shaders/VertShader.hpp"
#include "./shaders/ShaderProgram.hpp"

#include "./buffers/VAO.hpp"
#include "./buffers/VBO.hpp"
#include "./buffers/EBO.hpp"

#include "./obj/Board.hpp"
#include "./obj/Lines.hpp"
#include "./obj/Cube.hpp"

#include "./camera/camera.hpp"

#include "./debug/debug.hpp"

using namespace std;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {}

void handleEvents(GLFWwindow *window){
    
    if(glfwGetKey(window, GLFW_KEY_UP)==GLFW_PRESS){
        view = glm::translate(view, glm::vec3(0.0f, -0.01f, 0.0f));
    }
    else if(glfwGetKey(window, GLFW_KEY_RIGHT)==GLFW_PRESS){
        view = glm::translate(view, glm::vec3(-0.01f, 0.0f, 0.0f));
    }
    else if(glfwGetKey(window, GLFW_KEY_LEFT)==GLFW_PRESS){
        view = glm::translate(view, glm::vec3(0.01f, 0.0f, 0.0f));
    }
    else if(glfwGetKey(window, GLFW_KEY_DOWN)==GLFW_PRESS){
        view = glm::translate(view, glm::vec3(0.0f, 0.01f, 0.0f));
    }
    else if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS){
        zoom-=0.01f;
        if(zoom<=0.1f){
            zoom=0.1f;
        }
        projection = glm::perspective(glm::radians(45.0f*zoom), 1.0f, 0.1f, 100.0f);
    }
    else if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS){
        zoom+=0.01f;
        if(zoom>=3){
            zoom=3.0f;
        }
        projection = glm::perspective(glm::radians(45.0f*zoom), 1.0f, 0.1f, 100.0f);
    }
}

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 800, "Title", NULL, NULL);
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
    //glfwSetCursorPosCallback(window, mouse_callback);

    VertShader vertShader;
    FragShader fragShader;

    ShaderProgram shaderProgram;
    shaderProgram.attachShader(vertShader.compileShader(), fragShader.compileShader());

    vertShader.deleteShader();
    fragShader.deleteShader();

    //Board board;
    Lines lines;
    Cube cube;

    glEnable(GL_DEPTH_TEST);

    unsigned int modelLoc = glGetUniformLocation(shaderProgram.getProgram(), "model");
    unsigned int viewLoc = glGetUniformLocation(shaderProgram.getProgram(), "view");
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram.getProgram(), "projection");
    
    while(!glfwWindowShouldClose(window)){
        handleEvents(window);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.useProgram();

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        lines.renderLines();
        //board.renderBoard();
        cube.renderCube();
        
        cout << zoom << endl;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //board.deleteBoard();
    shaderProgram.deleteProgram();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

