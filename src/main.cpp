#include <iostream>
#include <string>
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

#include "./lighting/Lighting.hpp"

#include "./debug/debug.hpp"

using namespace std;

string glslPath = "./glsl/";

void mouse_callback(GLFWwindow* window, double xpos, double ypos){}

void handleEvents(GLFWwindow *window, Lighting lighting, unsigned int lightPosLoc){
    
    if(glfwGetKey(window, GLFW_KEY_UP)==GLFW_PRESS){//Move camera below
        view = glm::translate(view, glm::vec3(0.0f, -0.01f, 0.0f));
    }
    else if(glfwGetKey(window, GLFW_KEY_RIGHT)==GLFW_PRESS){
        view = glm::translate(view, glm::vec3(-0.01f, 0.0f, 0.0f));//Move camera to the right
    }
    else if(glfwGetKey(window, GLFW_KEY_LEFT)==GLFW_PRESS){
        view = glm::translate(view, glm::vec3(0.01f, 0.0f, 0.0f));//Move camera to the left
    }
    else if(glfwGetKey(window, GLFW_KEY_DOWN)==GLFW_PRESS){
        view = glm::translate(view, glm::vec3(0.0f, 0.01f, 0.0f));//Move camera up
    }
    else if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS){//Zoom OUT
        zoom-=0.01f;
        if(zoom<=0.1f){
            zoom=0.1f;
        }
    }
    else if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS){//Zoom IN
        zoom+=0.01f;
        if(zoom>=3){
            zoom=3.0f;
        }
    }
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

    //Set window coordinates.
    glViewport(0, 0, 800, 800);
    glfwSetCursorPosCallback(window, mouse_callback);

    //Init the program with standart shaders (3D).
    VertShader vertShader(glslPath + "fragmentShader.glsl");
    FragShader fragShader(glslPath + "vertexShader.glsl");

    ShaderProgram shaderProgram;
    shaderProgram.attachShader(vertShader.compileShader(), fragShader.compileShader());

    vertShader.deleteShader();
    fragShader.deleteShader();

    //Init objects.
    Lines lines;
    Cube cube;

    glEnable(GL_DEPTH_TEST); //Enable z-buffer.

    //Get camera uniform locations.
    unsigned int modelLoc = glGetUniformLocation(shaderProgram.getProgram(), "model");
    unsigned int viewLoc = glGetUniformLocation(shaderProgram.getProgram(), "view");
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram.getProgram(), "projection");

    //Get lighting uniform locations.
    unsigned int ambientStrenghtLoc = glGetUniformLocation(shaderProgram.getProgram(), "ambientStrength");
    unsigned int lightColorLoc = glGetUniformLocation(shaderProgram.getProgram(), "lightColor");
    unsigned int lightPosLoc = glGetUniformLocation(shaderProgram.getProgram(), "lightPos");
    unsigned int viewPosLoc = glGetUniformLocation(shaderProgram.getProgram(), "viewPos");
    
    Lighting lighting(0.1f, {1.0f, 0.5f, 1.0f});

    while(!glfwWindowShouldClose(window)){
        handleEvents(window, lighting, lightPosLoc);    //Handle events.
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   //Set color buffer to black.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear color buffer and z-buffer.
        //shaderProgram.useProgram(); //Use program.

        //Camera uniforms.
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        //Lighting uniforms.
        glUniform3fv(ambientStrenghtLoc, 1, glm::value_ptr(lighting.getAmbientStrenght()));
        glUniform3fv(lightColorLoc, 1, glm::value_ptr(lighting.getLightColor()));
        glUniform3fv(lightPosLoc, 1, glm::value_ptr(lighting.getLightPos()));
        glUniform3fv(viewPosLoc, 1, glm::value_ptr(cameraPos));

        //Render objects.
        lines.renderLines();
        cube.renderCube();
        
        //cout << zoom << endl;

        //Swap buffers and get pool events.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //Delete objects and program.
    shaderProgram.deleteProgram();

    //Destroy window and terminate GLFW.
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

