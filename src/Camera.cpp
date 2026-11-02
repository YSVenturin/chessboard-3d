#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 initialPosition, glm::vec3 target, glm::vec3 upDirection) {
    position = initialPosition;
    up = upDirection;

    front = glm::normalize(target - position);

    yaw = glm::degrees(glm::atan(front.z, front.x));
    pitch = glm::degrees(glm::asin(front.y));

    movementSpeed = 5.0f;
    rotationSpeed = 50.0f;
}

glm::mat4 Camera::getView() {
    return glm::lookAt(position, position + front, up);
}

void Camera::updateDirection(){
    glm::vec3 direction;
    direction.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    direction.y = glm::sin(glm::radians(pitch));
    direction.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    front = glm::normalize(direction);
}

void Camera::processInput(GLFWwindow* window, float timeDiff){
    float movementDistance = movementSpeed * timeDiff;
    float rotation = rotationSpeed * timeDiff;

    // rotation with up, left, right, down arrows
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        yaw -= rotation;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        yaw += rotation;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        pitch += rotation;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        pitch -= rotation;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    updateDirection();

    glm::vec3 right = glm::normalize(glm::cross(front, up));

    // movements
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += front * movementDistance;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= front * movementDistance;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= right * movementDistance;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += right * movementDistance;

    // vertical movements
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        position += up * movementDistance;
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        position -= up * movementDistance;
}
