#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace debug{
    void printMatrix(glm::mat4& mat){
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                std::cout << mat[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    void printVec3(glm::vec3& vec){
        for (int i = 0; i < 3; ++i) {
            std::cout << vec[i] << " ";
        }
        std::cout << std::endl;
    }
}