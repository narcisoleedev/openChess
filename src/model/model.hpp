

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Model {
public:
    Model(const std::string& path) {
        loadModel(path);
    }

    void draw(ShaderProgram& shader) {
        for (auto& mesh : meshes) {
            mesh.draw(shader);
        }
    }

private:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Mesh> meshes;
    string directory;

    void loadModel(const string& path) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
            return;
        }
        directory = path.substr(0, path.find_last_of('/'));

        processNode(scene->mRootNode, scene);
    }

    void processNode(aiNode* node, const aiScene* scene) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene);
        }
    }

    Mesh processMesh(aiMesh* mesh, const aiScene* scene) {
        vector<Vertex> vertices;
        vector<unsigned int> indices;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;
            vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
            if (mesh->mTextureCoords[0]) {
                vertex.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            } else {
                vertex.texCoords = glm::vec2(0.0f, 0.0f);
            }
            vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        return Mesh(vertices, indices);
    }
};

class Mesh {
public:
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices) {
        this->vertices = vertices;
        this->indices = indices;
        setupMesh();
    }

    void draw(ShaderProgram& shader) {
        vao.bindVertexArray();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        vao.unbindVertexArray();
    }

private:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    VAO vao;
    VBO vbo;
    EBO ebo;

    void setupMesh() {
        vao.genVertexArrays(1);
        vbo.genBuffer();
        ebo.genBuffer();

        vao.bindVertexArray();
        vbo.bindBuffer();
        vbo.bufferData(vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        ebo.bindBuffer();
        ebo.bufferData(indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        vao.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        vao.enableVertexArray(0);
        vao.vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        vao.enableVertexArray(1);
        vao.vertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
        vao.enableVertexArray(2);

        vbo.unbindBuffer();
        vao.unbindVertexArray();
        ebo.unbindBuffer();
    }
};