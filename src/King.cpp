#include "King.h"
#include <glm/gtc/matrix_transform.hpp>

King::King(glm::vec3 initialPosition, glm::vec3 pieceColor) : ChessPiece(initialPosition, pieceColor) {
}

void King::drawCylinderPart(Shader& shader, glm::mat4 parentModel, glm::vec3 localPosition, glm::vec3 dimensions) {
    cylinderPart.position = localPosition;
    cylinderPart.scale = dimensions;
    cylinderPart.draw(shader, parentModel);
}

void King::drawCubePart(Shader& shader, glm::mat4 parentModel, glm::vec3 localPosition,glm::vec3 dimensions) {
    cubePart.position = localPosition;
    cubePart.scale = dimensions;
    cubePart.draw(shader, parentModel);
}

void King::draw(Shader& shader, glm::mat4 model) {
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
    drawCylinderPart(shader, model, glm::vec3(0.0f, 0.08f, 0.0f), glm::vec3(0.76f, 0.16f, 0.76f));
    // Body
    drawCylinderPart(shader, model, glm::vec3(0.0f, 0.22f, 0.0f), glm::vec3(0.54f, 0.12f, 0.54f));
    drawCylinderPart(shader, model, glm::vec3(0.0f, 0.64f, 0.0f), glm::vec3(0.34f, 0.72f, 0.34f));
    drawCylinderPart(shader, model, glm::vec3(0.0f, 1.05f, 0.0f), glm::vec3(0.48f, 0.10f, 0.48f));
    // Top
    drawCylinderPart(shader, model, glm::vec3(0.0f, 1.16f, 0.0f),glm::vec3(0.56f, 0.12f, 0.56f));
    // Cross
    drawCubePart(shader, model, glm::vec3(0.0f, 1.40f, 0.0f), glm::vec3(0.10f, 0.36f, 0.10f));
    drawCubePart(shader, model, glm::vec3(0.0f, 1.45f, 0.0f),glm::vec3(0.32f, 0.10f, 0.10f));
}
