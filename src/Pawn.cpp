#include "Pawn.h"
#include <glm/gtc/matrix_transform.hpp>

Pawn::Pawn(glm::vec3 initialPosition, glm::vec3 pieceColor) : ChessPiece(initialPosition, pieceColor) {
}

void Pawn::drawCylinderPart(Shader& shader, glm::mat4 parentModel, glm::vec3 localPosition, glm::vec3 dimensions) {
    cylinderPart.position = localPosition;
    cylinderPart.scale = dimensions;
    cylinderPart.draw(shader, parentModel);
}

void Pawn::draw(Shader& shader, glm::mat4 model) {
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
    drawCylinderPart(shader, model, glm::vec3(0.0f, 0.08f, 0.0f), glm::vec3(0.68f, 0.16f, 0.68f));

    // Body
    drawCylinderPart(shader, model, glm::vec3(0.0f, 0.36f, 0.0f), glm::vec3(0.28f, 0.40f, 0.28f));

    drawCylinderPart(shader, model, glm::vec3(0.0f, 0.60f, 0.0f), glm::vec3(0.40f, 0.08f, 0.40f));

    // Top
    drawCylinderPart(shader, model, glm::vec3(0.0f, 0.75f, 0.0f), glm::vec3(0.46f, 0.22f, 0.46f));
}
