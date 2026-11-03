#include "Queen.h"
#include <glm/gtc/matrix_transform.hpp>

Queen::Queen(glm::vec3 initialPosition, glm::vec3 pieceColor) : ChessPiece(initialPosition, pieceColor) {
}

void Queen::drawCylinderPart(Shader& shader, glm::mat4 parentModel, glm::vec3 localPosition, glm::vec3 dimensions) {
    cylinderPart.position = localPosition;
    cylinderPart.scale = dimensions;
    cylinderPart.draw(shader, parentModel);
}

void Queen::drawCubePart(Shader& shader, glm::mat4 parentModel, glm::vec3 localPosition, glm::vec3 dimensions) {
    cubePart.position = localPosition;
    cubePart.scale = dimensions;
    cubePart.draw(shader, parentModel);
}

void Queen::draw(Shader& shader, glm::mat4 model) {
    model = glm::translate(model, position);

    if (glm::length(rotation) > 0.0f)
        model = glm::rotate(
            model,
            glm::radians(angle),
            glm::normalize(rotation)
        );

    model = glm::scale(model, scale);

    shader.setVec3("objectColor", color);

    // Base
    drawCylinderPart(shader, model, glm::vec3(0.0f, 0.08f, 0.0f), glm::vec3(0.72f, 0.16f, 0.72f));

    // Body
    drawCylinderPart(shader, model, glm::vec3(0.0f, 0.22f, 0.0f), glm::vec3(0.52f, 0.12f, 0.52f));
    drawCylinderPart(shader, model, glm::vec3(0.0f, 0.60f, 0.0f), glm::vec3(0.30f, 0.64f, 0.30f));
    drawCylinderPart(shader, model, glm::vec3(0.0f, 0.97f, 0.0f), glm::vec3(0.46f, 0.10f, 0.46f));

    // Crown
    drawCylinderPart(shader, model, glm::vec3(0.0f, 1.08f, 0.0f), glm::vec3(0.56f, 0.12f, 0.56f));
    drawCubePart(shader, model, glm::vec3(-0.18f, 1.23f, 0.0f), glm::vec3(0.12f, 0.18f, 0.12f));
    drawCubePart(shader, model, glm::vec3(0.18f, 1.23f, 0.0f), glm::vec3(0.12f, 0.18f, 0.12f));
    drawCubePart(shader, model, glm::vec3(0.0f, 1.23f, -0.18f), glm::vec3(0.12f, 0.18f, 0.12f));
    drawCubePart(shader, model, glm::vec3(0.0f, 1.23f, 0.18f), glm::vec3(0.12f, 0.18f, 0.12f));
    drawCylinderPart(shader, model, glm::vec3(0.0f, 1.26f, 0.0f), glm::vec3(0.18f, 0.24f, 0.18f));
}
