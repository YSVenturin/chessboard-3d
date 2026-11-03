#include "Knight.h"
#include <glm/gtc/matrix_transform.hpp>

Knight::Knight(glm::vec3 initialPosition, glm::vec3 pieceColor) : ChessPiece(initialPosition, pieceColor) {
}

void Knight::drawCubePart(Shader& shader, glm::mat4 parentModel, glm::vec3 localPosition, glm::vec3 dimensions, glm::vec3 rotationAxis, float rotationAngle) {
    cubePart.position = localPosition;
    cubePart.scale = dimensions;
    cubePart.rotation = rotationAxis;
    cubePart.angle = rotationAngle;
    cubePart.draw(shader, parentModel);
}

void Knight::draw(Shader& shader, glm::mat4 model) {
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
    cylinderPart.position = glm::vec3(0.0f, 0.08f, 0.0f);
    cylinderPart.scale = glm::vec3(0.68f, 0.16f, 0.68f);
    cylinderPart.draw(shader, model);

    // neck
    drawCubePart(shader, model, glm::vec3(0.0f, 0.46f, -0.06f), glm::vec3(0.25f, 0.56f, 0.28f), glm::vec3(1.0f, 0.0f, 0.0f), 15.0f);

    // Head
    drawCubePart(shader, model, glm::vec3(0.0f, 0.80f, 0.04f), glm::vec3(0.30f, 0.24f, 0.36f));
    drawCubePart(shader, model, glm::vec3(0.0f, 0.75f, 0.28f), glm::vec3(0.26f, 0.16f, 0.26f));

    // Left ear
    drawCubePart(shader, model, glm::vec3(-0.09f, 0.98f, -0.06f), glm::vec3(0.07f, 0.18f, 0.10f));

    // Right ear
    drawCubePart(shader, model,glm::vec3(0.09f, 0.98f, -0.06f), glm::vec3(0.07f, 0.18f, 0.10f));
}
