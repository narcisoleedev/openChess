#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unistd.h>

#include "../libs/stb_image.h"

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

#include "./lighting/Lighting.hpp"

#include "./debug/debug.hpp"

#include "./model/Model.hpp"

using namespace std;

string glslPath = "/src/glsl/";

char * resourcesPath = "src/resources/backpack.obj";
//char * resourcesPath = "src/resources/Chessset.obj";

void mouse_callback(GLFWwindow* window, double xpos, double ypos){}

void handleEvents(GLFWwindow *window, Camera& camera){
    
    if(glfwGetKey(window, GLFW_KEY_UP)==GLFW_PRESS){//Move camera below
        camera.view = glm::translate(camera.view, glm::vec3(0.0f, -0.01f, 0.0f));
    }
    else if(glfwGetKey(window, GLFW_KEY_RIGHT)==GLFW_PRESS){
        camera.view = glm::translate(camera.view, glm::vec3(-0.01f, 0.0f, 0.0f));//Move camera to the right
    }
    else if(glfwGetKey(window, GLFW_KEY_LEFT)==GLFW_PRESS){
        camera.view = glm::translate(camera.view, glm::vec3(0.01f, 0.0f, 0.0f));//Move camera to the left
    }
    else if(glfwGetKey(window, GLFW_KEY_DOWN)==GLFW_PRESS){
        camera.view = glm::translate(camera.view, glm::vec3(0.0f, 0.01f, 0.0f));//Move camera up
    }
    else if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS){//Zoom OUT
        camera.zoom-=0.01f;
        if(camera.zoom<=0.1f){
            camera.zoom=0.1f;
        }
    }
    else if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS){//Zoom IN
        camera.zoom+=0.01f;
        if(camera.zoom>=3){
            camera.zoom=3.0f;
        }
    }
    camera.projection = glm::perspective(glm::radians(45.0f * camera.zoom), 1.0f, 0.1f, 100.0f);
}

int main(){
    //Cria a janela e provê infos do OpenGL
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

    stbi_set_flip_vertically_on_load(true);

    //Set window coordinates.
    glViewport(0, 0, 800, 800);
    glfwSetCursorPosCallback(window, mouse_callback);


    Model ourModel(resourcesPath);
    VertShader vertexShader(glslPath + "vertexShaderModel.glsl");
    FragShader fragShader(glslPath + "fragmentShaderModel.glsl");
    ShaderProgram shaderProgram;
    shaderProgram.attachShader(vertexShader.compileShader(), fragShader.compileShader());
    vertexShader.deleteShader();
    fragShader.deleteShader();

    //Init objects.
    Lines lines;
    Cube cube;

    glEnable(GL_DEPTH_TEST); //Enable z-buffer.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Camera camera;
    Lighting lighting(0.1f, {0.0f, -1.5f, 10.0f});

    while(!glfwWindowShouldClose(window)){
        handleEvents(window, camera);    //Handle events.
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   //Set color buffer to black.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear color buffer and z-buffer.

        shaderProgram.useProgram(); //Use program.

        unsigned int modelLoc = glGetUniformLocation(shaderProgram.getProgram(), "model");
        unsigned int viewLoc = glGetUniformLocation(shaderProgram.getProgram(), "view");
        unsigned int projectionLoc = glGetUniformLocation(shaderProgram.getProgram(), "projection");

        //Camera uniforms.
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(camera.model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera.projection));

        ourModel.Draw(shaderProgram);

        //Render objects.
        cube.renderCube(camera, lighting);
        lines.renderLines(camera, lighting);
        
        //cout << zoom << endl;

        //Swap buffers and get pool events.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //Delete objects and program.
    cube.deleteCube();
    lines.deleteLines();

    //Destroy window and terminate GLFW.
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

