#pragma once

#include "Object.h"

class Pyramid : public Object {
public:
    Pyramid(glm::vec3 pos = glm::vec3(0.0f),
            glm::vec3 rot = glm::vec3(0.0f),
            glm::vec3 scl = glm::vec3(1.0f),
            float ang = 0.0f);

    void draw(Shader& shader, glm::mat4 model) override;

private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    GLsizei indexCount;

    void init();
};
