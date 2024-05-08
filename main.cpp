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

#include "./debug/debug.hpp"

using namespace std;

glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
float zoom = 0.0f;

void handleEvents(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_UP)==GLFW_PRESS){
        zoom+=0.1f;
        projection = glm::perspective(glm::radians(45.0f*zoom), 1.0f, 0.1f, 100.0f);
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT)==GLFW_PRESS){
        view = glm::translate(view, glm::vec3(0.01f, 0.0f, 0.0f));
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT)==GLFW_PRESS){
        view = glm::translate(view, glm::vec3(-0.01f, 0.0f, 0.0f));
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN)==GLFW_PRESS){
        zoom-=0.1f;
        projection = glm::perspective(glm::radians(45.0f*zoom), 1.0f, 0.1f, 100.0f);
    }
    if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS){
        view = glm::rotate(view, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 1.0f));
    }
    if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS){
        view = glm::rotate(view, glm::radians(1.0f), glm::vec3(0.0f, -1.0f, 1.0f));
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

    VertShader vertShader;
    FragShader fragShader;

    ShaderProgram shaderProgram;
    shaderProgram.attachShader(vertShader.compileShader(), fragShader.compileShader());

    vertShader.deleteShader();
    fragShader.deleteShader();

    Board board;

    VAO vao;
    VBO vbo;
    EBO ebo;

    vao.genVertexArrays(1);
    vbo.genBuffer();
    ebo.genBuffer();
    vao.bindVertexArray();

    vbo.bindBuffer();
    vbo.bufferData(sizeof(board.vertices)+sizeof(board.colors), GL_STATIC_DRAW);
    vbo.bufferSubData(0, sizeof(board.vertices), board.vertices);
    vbo.bufferSubData(sizeof(board.vertices), sizeof(board.colors), board.colors);

    ebo.bindBuffer();
    cout << sizeof(board.vertices) << endl;
    ebo.bufferData(sizeof(board.indices), board.indices, GL_STATIC_DRAW);

    vao.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    vao.enableVertexArray(0);
    vao.vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)(sizeof(board.vertices)));
    vao.enableVertexArray(1);

    vbo.unbindBuffer();
    vao.unbindVertexArray();
    ebo.unbindBuffer();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);

    unsigned int modelLoc = glGetUniformLocation(shaderProgram.getProgram(), "model");
    unsigned int viewLoc = glGetUniformLocation(shaderProgram.getProgram(), "view");
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram.getProgram(), "projection");

    //glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    //glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    //glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    //debug::printVec3(cameraDirection);
    //glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    //glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    //debug::printVec3(cameraRight);
    
    while(!glfwWindowShouldClose(window)){
        handleEvents(window);
        glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.useProgram();
        vao.bindVertexArray();
        //glm::mat4 res = model*view*projection;
        //debug::printMatrix(res);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glDrawElements(GL_TRIANGLES, sizeof(board.indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        vao.unbindVertexArray();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    vao.deleteVertexArrays();
    vbo.deleteBuffers();
    vbo.deleteBuffers();
    shaderProgram.deleteProgram();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

