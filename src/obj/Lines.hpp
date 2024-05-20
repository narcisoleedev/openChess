#include <iostream>
#include <glad/glad.h>

#include "../buffers/VAO.hpp"
#include "../buffers/VBO.hpp"
#include "../buffers/EBO.hpp"

class Lines{
    private:
    float vertices[21] = {
        0.0f, 0.0f, 0.0f, 
        10.0f, 0.0f, 0.0f,
        0.0f, 10.0f, 0.0f,
        0.0f, 0.0f, 10.0f,
        -10.0f, 0.0f, 0.0f,
        0.0f, -10.0f, 0.0f,
        0.0f, 0.0f, -10.0f,
    };
    
    float normals[21] = {
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
    };

    float colors[21] = {
        1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
    };

    int cord[12] = {
        0, 1, 
        0, 2,
        0, 3,
        0, 4, 
        0, 5,
        0, 6
    };

    VAO vao;
    VBO vbo;
    EBO ebo;

    void initLines(){
        vao.genVertexArrays(1);
        vbo.genBuffer();
        ebo.genBuffer();
        vao.bindVertexArray();
        vbo.bindBuffer();
        vbo.bufferData(sizeof(vertices)+sizeof(normals)+sizeof(colors), GL_STATIC_DRAW);
        vbo.bufferSubData(0, sizeof(vertices), vertices);
        vbo.bufferSubData(sizeof(vertices), sizeof(normals), normals);
        vbo.bufferSubData(sizeof(vertices)+sizeof(normals), sizeof(colors), colors);
        ebo.bindBuffer();
        ebo.bufferData(sizeof(cord), cord, GL_STATIC_DRAW);
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
    
    public:
    Lines(){
        initLines();
    }
    void renderLines(){
        vao.bindVertexArray();
        glDrawElements(GL_LINES, sizeof(cord)/sizeof(int), GL_UNSIGNED_INT, 0);
        vao.unbindVertexArray();
    }
    
    void deleteLines(){
        vao.deleteVertexArrays();
        vbo.deleteBuffers();
        ebo.deleteBuffers();
    }

};