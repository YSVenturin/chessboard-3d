#include "Bishop.h"
#include <glm/gtc/matrix_transform.hpp>

Bishop::Bishop(glm::vec3 initialPosition, glm::vec3 pieceColor) : ChessPiece(initialPosition, pieceColor) {
}

void Bishop::drawCylinderPart(Shader& shader, glm::mat4 parentModel, glm::vec3 localPosition, glm::vec3 dimensions) {
    cylinderPart.position = localPosition;
    cylinderPart.scale = dimensions;
    cylinderPart.draw(shader, parentModel);
}

void Bishop::draw(Shader& shader, glm::mat4 model) {
    model = glm::translate(model, position);

    if (glm::length(rotation) > 0.0f)
        model = glm::rotate(
            model,
            glm::radians(angle),
            glm::normalize(rotation)
        );

    model = glm::scale(model, scale);

    shader.setVec3("objectColor", color);

    // base
    drawCylinderPart(shader, model, glm::vec3(0.0f, 0.08f, 0.0f), glm::vec3(0.68f, 0.16f, 0.68f));

    // body
    drawCylinderPart(shader, model, glm::vec3(0.0f, 0.43f, 0.0f), glm::vec3(0.28f, 0.54f, 0.28f));
    drawCylinderPart(shader, model, glm::vec3(0.0f, 0.74f, 0.0f), glm::vec3(0.44f, 0.08f, 0.44f));

    // top - rotated cube
    cubePart.position = glm::vec3(0.0f, 0.95f, 0.0f);
    cubePart.scale = glm::vec3(0.24f, 0.30f, 0.18f);
    cubePart.rotation = glm::vec3(0.0f, 0.0f, 1.0f);
    cubePart.angle = 45.0f;
    cubePart.draw(shader, model);
}
