#pragma once
#include "ChessPiece.h"
#include "Cylinder.h"
#include "Cube.h"

class Knight : public ChessPiece {
public:
    Knight(glm::vec3 initialPosition, glm::vec3 pieceColor);
    void draw(Shader& shader, glm::mat4 model) override;

private:
    Cylinder cylinderPart;
    Cube cubePart;
    void drawCubePart(Shader& shader, glm::mat4 parentModel, glm::vec3 localPosition, glm::vec3 dimensions, glm::vec3 rotationAxis = glm::vec3(0.0f), float rotationAngle = 0.0f);
};
