#include "Cube.h"

static const float vertices[] = {
    // position        normal   tex coords
    
    // back (-Z)
   -0.5f,-0.5f,-0.5f,  0,0,-1,  0,1,
    0.5f,-0.5f,-0.5f,  0,0,-1,  1,1,
    0.5f, 0.5f,-0.5f,  0,0,-1,  1,0,
   -0.5f, 0.5f,-0.5f,  0,0,-1,  0,0,
    // front (+Z)
   -0.5f,-0.5f, 0.5f,  0,0,1,   0,0,
    0.5f,-0.5f, 0.5f,  0,0,1,   1,0,
    0.5f, 0.5f, 0.5f,  0,0,1,   1,1,
   -0.5f, 0.5f, 0.5f,  0,0,1,   0,1,
    // left (-X)
   -0.5f,-0.5f,-0.5f, -1,0,0,   1,1,
   -0.5f, 0.5f,-0.5f, -1,0,0,   1,0,
   -0.5f, 0.5f, 0.5f, -1,0,0,   0,0,
   -0.5f,-0.5f, 0.5f, -1,0,0,   0,1,
    // right (+X)
    0.5f,-0.5f,-0.5f,  1,0,0,   0,1,
    0.5f, 0.5f,-0.5f,  1,0,0,   0,0,
    0.5f, 0.5f, 0.5f,  1,0,0,   1,0,
    0.5f,-0.5f, 0.5f,  1,0,0,   1,1,
    // top (+Y)
   -0.5f, 0.5f,-0.5f,  0,1,0,   0,1,
    0.5f, 0.5f,-0.5f,  0,1,0,   1,1,
    0.5f, 0.5f, 0.5f,  0,1,0,   1,0,
   -0.5f, 0.5f, 0.5f,  0,1,0,   0,0,
    // bottom (-Y)
   -0.5f,-0.5f,-0.5f,  0,-1,0,  0,0,
    0.5f,-0.5f,-0.5f,  0,-1,0,  1,0,
    0.5f,-0.5f, 0.5f,  0,-1,0,  1,1,
   -0.5f,-0.5f, 0.5f,  0,-1,0,  0,1
};

static const unsigned int indices[] = {
    0,1,2, 2,3,0,        // back
    4,5,6, 6,7,4,        // front
    8,9,10, 10,11,8,     // left
    12,13,14, 14,15,12,  // right
    16,17,18, 18,19,16,  // top
    20,21,22, 22,23,20   // bottom
};

Cube::Cube(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle) : Object(pos, rot, scl, angle) {
    init();
}

void Cube::init() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position
    const GLsizei stride = 8 * sizeof(float);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    // tex coords
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Cube::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    if (glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));
    model = glm::scale(model, scale);

    shader.setMat4("model", model);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
