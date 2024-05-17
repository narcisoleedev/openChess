#include <iostream>
#include <vector>
#include <random>

#include "../buffers/VAO.hpp"
#include "../buffers/VBO.hpp"
#include "../buffers/EBO.hpp"

using namespace std;

class Board {

    private:
        float vertices[81*4*3];
        float colors[81*4*3];
        int indices[81*6];

        VAO vao;
        VBO vbo;
        EBO ebo;

    public:
        float randomFloat(float min, float max) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<float> dist(min, max);
        return dist(gen);
    }
        Board(){
            float cord[3] = {-0.5f, 0.0f, 0.0f};
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    vertices[(i * 9 + j) * 12] = cord[0];
                    cout << vertices[(i * 9 + j) * 12] << " ";
                    cord[0] += 0.15f;
                    vertices[(i * 9 + j) * 12 + 1] = cord[1];
                    cout << vertices[(i * 9 + j) * 12+1] << " ";
                    vertices[(i * 9 + j) * 12 + 2] = cord[2];
                    cout << vertices[(i * 9 + j) * 12+2]<<endl;

                    vertices[(i * 9 + j) * 12 + 3] = cord[0];
                    cout << vertices[(i * 9 + j) * 12+3] << " ";
                    vertices[(i * 9 + j) * 12 + 4] = cord[1];
                    cout << vertices[(i * 9 + j) * 12+4] << " ";
                    cord[1] += 0.15f;
                    vertices[(i * 9 + j) * 12 + 5] = cord[2];
                    cout << vertices[(i * 9 + j) * 12+5] << endl;

                    vertices[(i * 9 + j) * 12 + 6] = cord[0];
                    cout << vertices[(i * 9 + j) * 12+6] << " ";
                    cord[0] -= 0.15f;
                    vertices[(i * 9 + j) * 12 + 7] = cord[1];
                    cout << vertices[(i * 9 + j) * 12+7] << " ";
                    vertices[(i * 9 + j) * 12 + 8] = cord[2];
                    cout << vertices[(i * 9 + j) * 12+8] << endl;

                    vertices[(i * 9 + j) * 12 + 9] = cord[0];
                    cout << vertices[(i * 9 + j) * 12+9] << " ";
                    vertices[(i * 9 + j) * 12 + 10] = cord[1];
                    cout << vertices[(i * 9 + j) * 12+10] << " ";
                    cord[1] -= 0.15f;
                    vertices[(i * 9 + j) * 12 + 11] = cord[2];
                    cout << vertices[(i * 9 + j) * 12+11] << endl;
                    cord[0] += 0.15f;
                }
                cord[0] = -0.5f;
                cord[2] -= 0.15f;
            }

            int j = 0;
            for (int i = 0; i < 81 * 4 * 3; i++) {
                colors[i] = randomFloat(0.0f, 1.0f);
            }

            int firstRow=0;
            for(int i = 0; i<8; i++){
                for(int j = 0; j<8; j++){
                    indices[i*54+j*6] = ((i*8+j)*4);
                    indices[i*54+j*6+1] = ((i*8+j)*4)+1;
                    indices[i*54+j*6+2] = ((i*8+j)*4)+2;
                    indices[i*54+j*6+3] = ((i*8+j)*4)+2;
                    indices[i*54+j*6+4] = ((i*8+j)*4)+3;
                    indices[i*54+j*6+5] = ((i*8+j)*4);
                }
            }
            
            initBoard();
        }
        
        void initBoard(){
            vao.genVertexArrays(1);
            vbo.genBuffer();
            ebo.genBuffer();
            vao.bindVertexArray();

            vbo.bindBuffer();
            vbo.bufferData(sizeof(vertices)+sizeof(colors), GL_STATIC_DRAW);
            vbo.bufferSubData(0, sizeof(vertices), vertices);
            vbo.bufferSubData(sizeof(vertices), sizeof(colors), colors);

            ebo.bindBuffer();
            cout << sizeof(vertices) << endl;
            ebo.bufferData(sizeof(indices), indices, GL_STATIC_DRAW);

            vao.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
            vao.enableVertexArray(0);
            vao.vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)(sizeof(vertices)));
            vao.enableVertexArray(1);

            vbo.unbindBuffer();
            vao.unbindVertexArray();
            ebo.unbindBuffer();
        }

        void renderBoard(){
            vao.bindVertexArray();
            glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
            vao.unbindVertexArray();
        }
        
        void deleteBoard(){
            vao.deleteVertexArrays();
            vbo.deleteBuffers();
            ebo.deleteBuffers();
        }
};
