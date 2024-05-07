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

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    unsigned int transformLoc = glGetUniformLocation(shaderProgram.getProgram(), "transform");
    float angle = 0.0f;
    
    while(!glfwWindowShouldClose(window)){
        if(glfwGetKey(window, GLFW_KEY_UP)==GLFW_PRESS){
            angle+=0.1f;
        }
        if(glfwGetKey(window, GLFW_KEY_DOWN)==GLFW_PRESS){
            angle-=0.1f;
        }
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.useProgram();
        vao.bindVertexArray();
        glm::vec3 axis(0.0f, 1.0f, 1.0f); // Arbitrary axis, for example, rotating around (1,1,1)
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, axis);
        glm::vec3 translation(0.5f, -0.5f, 0.0f); // Same translation as before
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translation);
        glm::mat4 trans = translationMatrix * rotation;
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
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

