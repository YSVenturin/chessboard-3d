#include "Rook.h"
#include <glm/gtc/matrix_transform.hpp>

Rook::Rook(glm::vec3 initialPosition,glm::vec3 pieceColor) : ChessPiece(initialPosition, pieceColor){
}

void Rook::drawCubePart(Shader& shader, glm::mat4 parentModel, glm::vec3 localPosition, glm::vec3 dimensions){
    cubePart.position = localPosition;
    cubePart.scale = dimensions;
    cubePart.draw(shader, parentModel);
}

void Rook::draw(Shader& shader, glm::mat4 model){
    model = glm::translate(model, position);

    if (glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));

    model = glm::scale(model, scale);

    shader.setVec3("objectColor", color);

    drawCubePart(shader, model, glm::vec3(0.0f, 0.10f, 0.0f), glm::vec3(0.70f, 0.20f, 0.70f));
    drawCubePart(shader, model, glm::vec3(0.0f, 0.50f, 0.0f), glm::vec3(0.40f, 0.60f, 0.40f));
    drawCubePart(shader, model, glm::vec3(0.0f, 0.85f, 0.0f), glm::vec3(0.65f, 0.10f, 0.65f));
    drawCubePart(shader, model, glm::vec3(-0.22f, 0.975f, -0.22f), glm::vec3(0.20f, 0.15f, 0.20f));
    drawCubePart(shader, model, glm::vec3(0.22f, 0.975f, -0.22f), glm::vec3(0.20f, 0.15f, 0.20f));
    drawCubePart(shader, model, glm::vec3(-0.22f, 0.975f, 0.22f), glm::vec3(0.20f, 0.15f, 0.20f));
    drawCubePart(shader, model, glm::vec3(0.22f, 0.975f, 0.22f), glm::vec3(0.20f, 0.15f, 0.20f));
}
