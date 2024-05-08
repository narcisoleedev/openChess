/*#include <malloc.h>
#include <iostream>
#include <vector>

class Board{
    public:
    float* vertices;
    float* colors;
    int* indices;
    Board(){
        float* squares = (float*)malloc(sizeof(float)*81*4*3);
        float cord[3] = {-0.5f, 0.0f, 0.0f};
        for(int i=0; int i<=8; i++){
            for(int j=0; int j<=8; j++){
                squares[i*96+j*12] = cord[0];
                cord[0]+=0.1f;
                squares[i*96+j*12+1] = cord[1];
                squares[i*96+j*12+2] = cord[2];

                squares[i*96+j*12+3] = cord[0];
                squares[i*96+j*12+4] = cord[1];
                cord[1]+=0.1f;
                squares[i*96+j*12+5] = cord[2];

                squares[i*96+j*12+6] = cord[0];
                cord[0]-=0.1f;
                squares[i*96+j*12+7] = cord[1];
                squares[i*96+j*12+8] = cord[2];

                squares[i*96+j*12+9] = cord[0];
                squares[i*96+j*12+10] = cord[1];
                cord[1]-=0.1f;
                squares[i*96+j*12+11] = cord[2];
            }
            cord[0]+=0.1f;
        }
        cord[0]=0.5f;
        cord[2]-=0.1f;
    }
    vertices = squares;
    free(squares);
    float* squarescolors = (float*)malloc(sizeof(float)*81*4*3);
    for(int i=0; i<81*4*3; i++) squarescolors[i]=1.0f;
    colors = squarescolors;
    free(squarescolors);

    // Generate indices
        std::vector<int> squareIndices;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                int topLeft = i * 64 + j * 8;
                int topRight = topLeft + 1;
                int bottomRight = (i + 1) * 64 + (j + 1) * 8;
                int bottomLeft = bottomRight - 1;

                // First triangle
                squareIndices.push_back(topLeft);
                squareIndices.push_back(topRight);
                squareIndices.push_back(bottomRight);

                // Second triangle
                squareIndices.push_back(bottomRight);
                squareIndices.push_back(bottomLeft);
                squareIndices.push_back(topLeft);
            }
        }

        // Convert vector to array
        int* indicesArray = new int[squareIndices.size()];
        std::copy(squareIndices.begin(), squareIndices.end(), indicesArray);

        indices = indicesArray;
};*/

#include <iostream>
#include <vector>
#include <random>

using namespace std;

class Board {
public:
    float vertices[81*4*3];
    float colors[81*4*3];
    int indices[81*6];

    float randomFloat(float min, float max) {
    // Create a random device
    random_device rd;
    
    // Create a random number engine
    mt19937 gen(rd());
    
    // Create a uniform distribution for floats
    uniform_real_distribution<float> dist(min, max);
    
    // Generate and return a random float
    return dist(gen);
}
    Board() {
        // Allocate memory for vertices
        //vertices = float[81 * 4 * 3];
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

        // Allocate memory for colors
        for (int i = 0; i < 81 * 4 * 3; i++) 
            colors[i] = randomFloat(0.0f, 1.0f);

        // Generate indices
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
        
    }
};

/*
#include <iostream>
#include <vector>

using namespace std;

class Board {
    public:
        float vertices[24] = {
                -0.1f, -0.1f, -0.1f,
                0.1f, -0.1f, -0.1f,
                0.1f, 0.1f, -0.1f,
                0.1f, -0.1f, -0.1f,
                -0.1f, -0.1f, 0.1f,
                0.1f, -0.1f, 0.1f,
                0.1f, 0.1f, 0.1f,
                0.1f, -0.1f, 0.1f,
        };
        float colors[24]= {
                1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f,
                
        };
        int indices[24]= {
                0, 1, 2,
                2, 3, 0,
                0, 3, 4,
                3, 4, 7,
                1, 5, 2,
                2, 5, 6,
                4, 5, 6,
                6, 7, 4
        };
        Board(){
            
        }
};*/