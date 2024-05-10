#include <iostream>
#include <vector>
#include <string.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "./buffers/VAO.hpp"
#include "./buffers/VBO.hpp"
#include "./buffers/EBO.hpp"

#include "../main.cpp"

using namespace std;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    string type;
};

class Mesh {
    public:
    VAO vao;
    VBO vbo;
    EBO ebo;
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices,
        vector<Texture> textures)
        {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
        setupMesh();
        }
    void Draw(Shader &shader){
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        for(unsigned int i = 0; i < textures.size(); i++)
        {
        glActiveTexture(GL_TEXTURE0 + i); // activate texture unit first
        // retrieve texture number (the N in diffuse_textureN)
        string number;
        string name = textures[i].type;
        if(name == "texture_diffuse")
        number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
        number = std::to_string(specularNr++);
        shader.setFloat(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }
        glActiveTexture(GL_TEXTURE0);
        // draw mesh
        vao.bindVertexArray();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        vao.unbindVertexArray();
    }
    private:
    void setupMesh()
    {
        vao.genVertexArrays(1);
        vbo.genBuffer();
        ebo.genBuffer();
        vao.bindVertexArray();
        vbo.bindBuffer();
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        ebo.bindBuffer();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() *
        sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        vao.enableVertexArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        vao.enableVertexArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        vbo.unbindBuffer();
        vao.unbindVertexArray();
        ebo.unbindBuffer();
    }};