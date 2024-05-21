#include <iostream>
#include <glad/glad.h>

#include "../buffers/VAO.hpp"
#include "../buffers/VBO.hpp"
#include "../buffers/EBO.hpp"

class Cube{
    private:
    /*
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

    float normals[24] = {
    // Front face
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    // Back face
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    };

    
    float colors[24] = {
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
    };

    int indices[36] = {
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
    };*/
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
        0.1f, 0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        // Back face (blue)
        0.1f, 0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        // Top face (blue)
        0.1f, 0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        // Bottom face (blue)
        0.1f, 0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        // Left face (blue)
        0.1f, 0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        // Right face (blue)
        0.1f, 0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
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


    VAO vao;
    VBO vbo;
    EBO ebo;

    void initCube(){
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
    
    public:
    Cube(){
        initCube();
    }
    void renderCube(){
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

