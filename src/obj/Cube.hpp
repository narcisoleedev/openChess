#include <iostream>
#include <glad/glad.h>

#include "../shaders/ShaderProgram.hpp"
#include "../shaders/VertShader.hpp"
#include "../shaders/FragShader.hpp"

#include "../buffers/VAO.hpp"
#include "../buffers/VBO.hpp"
#include "../buffers/EBO.hpp"

#include "../camera/camera.hpp"
#include "../lighting/Lighting.hpp"

class Cube{

    private:
        float vertices[72] = {
        // Front face
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        // Back face
        0.0f, 0.0f, 0.5f,
        0.5f, 0.0f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.0f, 0.5f, 0.5f,
        // Top face
        0.0f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.5f,
        0.0f, 0.5f, 0.5f,
        // Bottom face
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.5f,
        0.0f, 0.0f, 0.5f,
        // Left face
        0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.5f,
        0.0f, 0.0f, 0.5f,
        // Right face
        0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.0f, 0.5f
        };

        float normals[72] = {
            // Front face normals
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,
            // Back face normals
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            // Top face normals
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            // Bottom face normals
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            // Left face normals
            -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,
            // Right face normals
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f
        };

        float colors[72] = {
            // Front face (blue)
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            // Back face (blue)
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            // Top face (blue)
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            // Bottom face (blue)
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            // Left face (blue)
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            // Right face (blue)
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
        };
        int indices[36] = {
            // Front face
            0, 1, 2,
            2, 3, 0,
            // Back face
            4, 5, 6,
            6, 7, 4,
            // Top face
            8, 9, 10,
            10, 11, 8,
            // Bottom face
            12, 13, 14,
            14, 15, 12,
            // Left face
            16, 17, 18,
            18, 19, 16,
            // Right face
            20, 21, 22,
            22, 23, 20
        };

        ShaderProgram shaderProgram;
        VAO vao;
        VBO vbo;
        EBO ebo;

    void objectShader(VertShader vertexShader, FragShader fragShader){
        shaderProgram.attachShader(vertexShader.compileShader(), fragShader.compileShader());
        vertexShader.deleteShader();
        fragShader.deleteShader();
    }

    void initCube(){
        VertShader vertexShader("/src/glsl/vertexShader.glsl");
        FragShader fragShader("/src/glsl/fragmentShader.glsl");
        objectShader(vertexShader, fragShader);
        vao.genVertexArrays(1);
        vbo.genBuffer();
        ebo.genBuffer();
        vao.bindVertexArray();
        vbo.bindBuffer();
        vbo.bufferData(sizeof(vertices)+sizeof(normals)+sizeof(colors), GL_STATIC_DRAW);
        vbo.bufferSubData(0, sizeof(vertices), vertices);
        vbo.bufferSubData(sizeof(vertices), sizeof(normals), normals);
        vbo.bufferSubData(sizeof(vertices) + sizeof(normals), sizeof(colors), colors);
        ebo.bindBuffer();
        ebo.bufferData(sizeof(indices), indices, GL_STATIC_DRAW);
        vao.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        vao.enableVertexArray(0);
        vao.vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)(sizeof(vertices)));
        vao.enableVertexArray(1);
        vao.vertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)(sizeof(vertices)+sizeof(normals)));
        vao.enableVertexArray(2);
        vbo.unbindBuffer();
        vao.unbindVertexArray();
        ebo.unbindBuffer();
    }
    void uniforms(Camera& camera, Lighting& lighting){
        //Get lighting uniform locations.
        unsigned int ambientStrenghtLoc = glGetUniformLocation(shaderProgram.getProgram(), "ambientStrength");
        unsigned int lightColorLoc = glGetUniformLocation(shaderProgram.getProgram(), "lightColor");
        unsigned int lightPosLoc = glGetUniformLocation(shaderProgram.getProgram(), "lightPos");
        unsigned int viewPosLoc = glGetUniformLocation(shaderProgram.getProgram(), "viewPos");

        unsigned int modelLoc = glGetUniformLocation(shaderProgram.getProgram(), "model");
        unsigned int viewLoc = glGetUniformLocation(shaderProgram.getProgram(), "view");
        unsigned int projectionLoc = glGetUniformLocation(shaderProgram.getProgram(), "projection");

        //Camera uniforms.
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(camera.model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera.projection));

        //Lighting uniforms.
        glUniform3fv(ambientStrenghtLoc, 1, glm::value_ptr(lighting.getAmbientStrenght()));
        glUniform3fv(lightColorLoc, 1, glm::value_ptr(lighting.getLightColor()));
        glUniform3fv(lightPosLoc, 1, glm::value_ptr(lighting.getLightPos()));
        glUniform3fv(viewPosLoc, 1, glm::value_ptr(camera.cameraPos));

    }    
    public:
    Cube(){
        initCube();
    }
    void renderCube(Camera& camera, Lighting& lighting){
        shaderProgram.useProgram();
        uniforms(camera, lighting);
        vao.bindVertexArray();
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        vao.unbindVertexArray();
    }
    
    void deleteCube(){
        vao.deleteVertexArrays();
        vbo.deleteBuffers();
        ebo.deleteBuffers();
    }
};

