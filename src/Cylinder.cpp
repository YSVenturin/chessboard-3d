#include "Cylinder.h"
#include <vector>
#include <cmath>

Cylinder::Cylinder(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang)
    : Object(pos, rot, scl, ang) {
    init();
}

void Cylinder::init() {
    const int segments = 8;
    const float pi = 3.14159265359f;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    // Já tinha codigo pronto para gerar a estrutura dos cilindros
    // Isso evita ter que manual ter que ficar ajustando as posições (tinha muitas kkkk)

    // Laterais: anel inferior e superior
    for (int ring = 0; ring < 2; ++ring) {
        float y = (ring == 0) ? -0.5f : 0.5f;
        float v = (ring == 0) ? 0.0f : 1.0f;
        for (int i = 0; i <= segments; ++i) {
            float angle = 2.0f * pi * static_cast<float>(i) / segments;
            float x = 0.5f * std::cos(angle);
            float z = 0.5f * std::sin(angle);
            float nx = std::cos(angle);
            float nz = std::sin(angle);
            float u = static_cast<float>(i) / segments;
            vertices.insert(vertices.end(), {x, y, z, nx, 0.0f, nz, u, v});
        }
    }

    // Faces laterais (8 segmentos, dois triângulos por segmento)
    for (int i = 0; i < segments; ++i) {
        unsigned int bottom = static_cast<unsigned int>(i);
        unsigned int top = static_cast<unsigned int>(segments + 1 + i);
        indices.insert(indices.end(), {
            bottom, top, top + 1,
            top + 1, bottom + 1, bottom
        });
    }

    // Tampa inferior: normal constante para -Y
    const unsigned int bottomCenter = static_cast<unsigned int>(vertices.size() / 8);
    vertices.insert(vertices.end(), {0.0f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.5f, 0.5f});
    const unsigned int bottomRing = static_cast<unsigned int>(vertices.size() / 8);
    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * pi * static_cast<float>(i) / segments;
        float x = 0.5f * std::cos(angle);
        float z = 0.5f * std::sin(angle);
        vertices.insert(vertices.end(), {x, -0.5f, z, 0.0f, -1.0f, 0.0f, 0.5f + x, 0.5f + z});
    }
    for (int i = 0; i < segments; ++i) {
        unsigned int current = bottomRing + static_cast<unsigned int>(i);
        unsigned int next = bottomRing + static_cast<unsigned int>((i + 1) % segments);
        indices.insert(indices.end(), {bottomCenter, current, next});
    }

    // Tampa superior: normal constante para +Y
    const unsigned int topCenter = static_cast<unsigned int>(vertices.size() / 8);
    vertices.insert(vertices.end(), {0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f});
    const unsigned int topRing = static_cast<unsigned int>(vertices.size() / 8);
    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * pi * static_cast<float>(i) / segments;
        float x = 0.5f * std::cos(angle);
        float z = 0.5f * std::sin(angle);
        vertices.insert(vertices.end(), {x, 0.5f, z, 0.0f, 1.0f, 0.0f,
                                         0.5f + x, 0.5f + z});
    }
    for (int i = 0; i < segments; ++i) {
        unsigned int current = topRing + static_cast<unsigned int>(i);
        unsigned int next = topRing + static_cast<unsigned int>((i + 1) % segments);
        // ordem invertida para a face superior apontar para +Y
        indices.insert(indices.end(), {topCenter, next, current});
    }

    indexCount = static_cast<GLsizei>(indices.size());

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    const GLsizei stride = 8 * sizeof(float);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Cylinder::draw(Shader& shader, glm::mat4 model) {
    model = glm::translate(model, position);
    if (glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));
    model = glm::scale(model, scale);

    shader.setMat4("model", model);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
