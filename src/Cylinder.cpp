#include "Cylinder.h"

static const float vertices[] = {
    // positions                       // tex coords

    // Side: bottom ring (0-8)
     0.500000f, -0.5f,  0.000000f,     0.000f, 0.0f,
     0.353553f, -0.5f,  0.353553f,     0.125f, 0.0f,
     0.000000f, -0.5f,  0.500000f,     0.250f, 0.0f,
    -0.353553f, -0.5f,  0.353553f,     0.375f, 0.0f,
    -0.500000f, -0.5f,  0.000000f,     0.500f, 0.0f,
    -0.353553f, -0.5f, -0.353553f,     0.625f, 0.0f,
     0.000000f, -0.5f, -0.500000f,     0.750f, 0.0f,
     0.353553f, -0.5f, -0.353553f,     0.875f, 0.0f,
     0.500000f, -0.5f,  0.000000f,     1.000f, 0.0f,

    // Side: top ring (9-17)
     0.500000f,  0.5f,  0.000000f,     0.000f, 1.0f,
     0.353553f,  0.5f,  0.353553f,     0.125f, 1.0f,
     0.000000f,  0.5f,  0.500000f,     0.250f, 1.0f,
    -0.353553f,  0.5f,  0.353553f,     0.375f, 1.0f,
    -0.500000f,  0.5f,  0.000000f,     0.500f, 1.0f,
    -0.353553f,  0.5f, -0.353553f,     0.625f, 1.0f,
     0.000000f,  0.5f, -0.500000f,     0.750f, 1.0f,
     0.353553f,  0.5f, -0.353553f,     0.875f, 1.0f,
     0.500000f,  0.5f,  0.000000f,     1.000f, 1.0f,

    // Bottom cap: center (18)
     0.000000f, -0.5f,  0.000000f,     0.500000f, 0.500000f,

    // Bottom cap: ring (19-26)
     0.500000f, -0.5f,  0.000000f,     1.000000f, 0.500000f,
     0.353553f, -0.5f,  0.353553f,     0.853553f, 0.853553f,
     0.000000f, -0.5f,  0.500000f,     0.500000f, 1.000000f,
    -0.353553f, -0.5f,  0.353553f,     0.146447f, 0.853553f,
    -0.500000f, -0.5f,  0.000000f,     0.000000f, 0.500000f,
    -0.353553f, -0.5f, -0.353553f,     0.146447f, 0.146447f,
     0.000000f, -0.5f, -0.500000f,     0.500000f, 0.000000f,
     0.353553f, -0.5f, -0.353553f,     0.853553f, 0.146447f,

    // Top cap: center (27)
     0.000000f,  0.5f,  0.000000f,     0.500000f, 0.500000f,

    // Top cap: ring (28-35)
     0.500000f,  0.5f,  0.000000f,     1.000000f, 0.500000f,
     0.353553f,  0.5f,  0.353553f,     0.853553f, 0.853553f,
     0.000000f,  0.5f,  0.500000f,     0.500000f, 1.000000f,
    -0.353553f,  0.5f,  0.353553f,     0.146447f, 0.853553f,
    -0.500000f,  0.5f,  0.000000f,     0.000000f, 0.500000f,
    -0.353553f,  0.5f, -0.353553f,     0.146447f, 0.146447f,
     0.000000f,  0.5f, -0.500000f,     0.500000f, 0.000000f,
     0.353553f,  0.5f, -0.353553f,     0.853553f, 0.146447f
};

static const unsigned int indices[] = {
    // Side faces
    0, 9, 10,    10, 1, 0,
    1, 10, 11,   11, 2, 1,
    2, 11, 12,   12, 3, 2,
    3, 12, 13,   13, 4, 3,
    4, 13, 14,   14, 5, 4,
    5, 14, 15,   15, 6, 5,
    6, 15, 16,   16, 7, 6,
    7, 16, 17,   17, 8, 7,

    // Bottom cap
    18, 19, 20,
    18, 20, 21,
    18, 21, 22,
    18, 22, 23,
    18, 23, 24,
    18, 24, 25,
    18, 25, 26,
    18, 26, 19,

    // Top cap
    27, 29, 28,
    27, 30, 29,
    27, 31, 30,
    27, 32, 31,
    27, 33, 32,
    27, 34, 33,
    27, 35, 34,
    27, 28, 35
};

Cylinder::Cylinder(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang)
    : Object(pos, rot, scl, ang) {
    init();
}

void Cylinder::init() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Cylinder::draw(Shader& shader, glm::mat4 model) {
    model = glm::translate(model, position);

    if (glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));

    model = glm::scale(model, scale);

    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 96, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
