#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera{
public:
    Camera(glm::vec3 initialPosition, glm::vec3 target, glm::vec3 upDirection);
    void processInput(GLFWwindow* window, float deltaTime);
    glm::mat4 getView();

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;

    float yaw;
    float pitch;
    float movementSpeed;
    float rotationSpeed;
    void updateDirection();
};
