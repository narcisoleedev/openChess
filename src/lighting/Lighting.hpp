#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Lighting{
    private:
        float ambientStrength;
        glm::vec3 lightColor;
    public:
        glm::vec3 lightPos;
        Lighting(float ambientStrenght, glm::vec3 lightPos){
            this->ambientStrength = ambientStrenght;
            lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
            this->lightPos = lightPos;
            std::cout << sizeof(Lighting) << std::endl;
        }
        glm::vec3 getAmbientStrenght(){
            return glm::vec3(ambientStrength);
        }
        glm::vec3 getLightColor(){
            return lightColor;
        }
        glm::vec3 getLightPos(){
            return lightPos;
        }
};

