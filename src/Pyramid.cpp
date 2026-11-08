#include "Pyramid.h"

#include <vector>
#include <glm/geometric.hpp>

namespace {
    // Cada triangulo possui vertices proprios para manter a iluminacao plana.
    void addTriangle(std::vector<float>& vertices,
                     std::vector<unsigned int>& indices,
                     const glm::vec3& a,
                     const glm::vec3& b,
                     const glm::vec3& c) {
        const glm::vec3 normal = glm::normalize(glm::cross(b - a, c - a));
        const glm::vec2 uvs[3] = {
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(0.5f, 1.0f)
        };
        const glm::vec3 points[3] = {a, b, c};
        const unsigned int first = static_cast<unsigned int>(vertices.size() / 8);

        for (int i = 0; i < 3; ++i) {
            vertices.insert(vertices.end(), {
                points[i].x, points[i].y, points[i].z,
                normal.x, normal.y, normal.z,
                uvs[i].x, uvs[i].y
            });
        }

        indices.insert(indices.end(), {first, first + 1, first + 2});
    }
}

Pyramid::Pyramid(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang)
    : Object(pos, rot, scl, ang), VAO(0), VBO(0), EBO(0), indexCount(0) {
    init();
}

void Pyramid::init() {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    const glm::vec3 a(-0.5f, -0.5f, -0.5f);
    const glm::vec3 b( 0.5f, -0.5f, -0.5f);
    const glm::vec3 c( 0.5f, -0.5f,  0.5f);
    const glm::vec3 d(-0.5f, -0.5f,  0.5f);
    const glm::vec3 tip(0.0f, 0.5f, 0.0f);

    addTriangle(vertices, indices, a, tip, b); // front
    addTriangle(vertices, indices, b, tip, c); // right
    addTriangle(vertices, indices, c, tip, d); // back
    addTriangle(vertices, indices, d, tip, a); // left

    // Base
    addTriangle(vertices, indices, a, b, c);
    addTriangle(vertices, indices, a, c, d);

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

void Pyramid::draw(Shader& shader, glm::mat4 model) {
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
