#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Model
glm::mat4 model = glm::mat4(1.0f); 

//View
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::mat4 view = glm::lookAt(cameraPos,
                             glm::vec3(0.0f, 0.0f, 0.0f),
                             glm::vec3(0.0f, 1.0f, 0.0f)
                            );  

//Projection                            
glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
float zoom = 1.0f;

