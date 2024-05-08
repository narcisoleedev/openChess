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

using namespace std;

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
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram.getProgram(), "projection");

    //float angle = 0.0f;

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    
    while(!glfwWindowShouldClose(window)){
        /*
        if(glfwGetKey(window, GLFW_KEY_UP)==GLFW_PRESS){
            angle+=0.1f;
        }
        if(glfwGetKey(window, GLFW_KEY_DOWN)==GLFW_PRESS){
            angle-=0.1f;
        }
        */
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -0.01f));
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.useProgram();
        vao.bindVertexArray();
        //glm::vec3 axis(0.0f, 1.0f, 1.0f); // Arbitrary axis, for example, rotating around (1,1,1)
        //glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, axis);
        //glm::vec3 translation(0.5f, -0.5f, 0.0f); // Same translation as before
        //glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translation);
        //glm::mat4 trans = translationMatrix * rotation;
        glm::mat4 model = glm::mat4(1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glDrawElements(GL_TRIANGLES, sizeof(board.indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
        vao.unbindVertexArray();
    }
    vao.deleteVertexArrays();
    vbo.deleteBuffers();
    vbo.deleteBuffers();
    shaderProgram.deleteProgram();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

