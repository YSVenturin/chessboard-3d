#include "Sphere.h"
#include <vector>
#include <cmath>

Sphere::Sphere(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang)
    : Object(pos, rot, scl, ang), VAO(0), VBO(0), EBO(0), indexCount(0) {
    init();
}

void Sphere::init() {
    // Esfera UV com raio 0.5: suas dimensoes seguem o mesmo padrao
    // de Cube e Cylinder, sendo controladas pelo atributo scale.
    const unsigned int sectors = 24;
    const unsigned int stacks = 16;
    const float pi = 3.14159265359f;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i <= stacks; ++i) {
        const float stackAngle = pi * 0.5f -
            static_cast<float>(i) * pi / static_cast<float>(stacks);
        const float ringRadius = 0.5f * std::cos(stackAngle);
        const float y = 0.5f * std::sin(stackAngle);

        for (unsigned int j = 0; j <= sectors; ++j) {
            const float sectorAngle = 2.0f * pi *
                static_cast<float>(j) / static_cast<float>(sectors);

            const float x = ringRadius * std::cos(sectorAngle);
            const float z = ringRadius * std::sin(sectorAngle);

            // Posicao, normal suave e coordenadas UV (stride de 8 floats).
            vertices.insert(vertices.end(), {
                x, y, z,
                2.0f * x, 2.0f * y, 2.0f * z,
                static_cast<float>(j) / static_cast<float>(sectors),
                static_cast<float>(i) / static_cast<float>(stacks)
            });
        }
    }

    for (unsigned int i = 0; i < stacks; ++i) {
        const unsigned int upperRow = i * (sectors + 1);
        const unsigned int lowerRow = upperRow + sectors + 1;

        for (unsigned int j = 0; j < sectors; ++j) {
            const unsigned int a = upperRow + j;
            const unsigned int b = a + 1;
            const unsigned int c = lowerRow + j;
            const unsigned int d = c + 1;

            // Evita triangulos degenerados nos polos e mantem as faces
            // orientadas para fora (winding anti-horario visto de fora).
            if (i != 0) {
                indices.insert(indices.end(), {a, b, c});
            }
            if (i != stacks - 1) {
                indices.insert(indices.end(), {b, d, c});
            }
        }
    }

    indexCount = static_cast<GLsizei>(indices.size());

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 indices.data(), GL_STATIC_DRAW);

    const GLsizei stride = 8 * sizeof(float);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride,
                          (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Sphere::draw(Shader& shader, glm::mat4 model) {
    model = glm::translate(model, position);

    if (glm::length(rotation) > 0.0f) {
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));
    }

    model = glm::scale(model, scale);
    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
