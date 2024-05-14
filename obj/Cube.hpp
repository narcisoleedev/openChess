#include <iostream>
#include <glad/glad.h>

#include "../buffers/VAO.hpp"
#include "../buffers/VBO.hpp"
#include "../buffers/EBO.hpp"

class Cube{
    private:
    float vertices[24] = {
        0.0f, 0.0f, 0.0f, 
        0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.5f, 
        0.5f, 0.0f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.0f, 0.5f, 0.5f,
    };

    float colors[24] = {
        1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,
    };

    int cord[36] = {
        0, 1, 2,
        2, 3, 0,
        0, 1, 5,
        5, 4, 0,
        3, 2, 6,
        6, 7, 3,
        4, 5, 6,
        6, 7, 4,
        0, 3, 7, 
        7, 4, 0,
        1, 5, 6,
        6, 2, 1
    };

    VAO vao;
    VBO vbo;
    EBO ebo;

    void initCube(){
        vao.genVertexArrays(1);
        vbo.genBuffer();
        ebo.genBuffer();
        vao.bindVertexArray();
        vbo.bindBuffer();
        vbo.bufferData(sizeof(vertices)+sizeof(colors), GL_STATIC_DRAW);
        vbo.bufferSubData(0, sizeof(vertices), vertices);
        vbo.bufferSubData(sizeof(vertices), sizeof(colors), colors);
        ebo.bindBuffer();
        ebo.bufferData(sizeof(cord), cord, GL_STATIC_DRAW);
        vao.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        vao.enableVertexArray(0);
        vao.vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)(sizeof(vertices)));
        vao.enableVertexArray(1);
        vbo.unbindBuffer();
        vao.unbindVertexArray();
        ebo.unbindBuffer();
    }
    
    public:
    Cube(){
        initCube();
    }
    void renderCube()
    {
        vao.bindVertexArray();
        glDrawElements(GL_TRIANGLES, sizeof(cord)/sizeof(int), GL_UNSIGNED_INT, 0);
        vao.unbindVertexArray();
    }

};