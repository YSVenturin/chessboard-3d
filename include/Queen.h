#pragma once
#include "ChessPiece.h"
#include "Cylinder.h"
#include "Cube.h"

class Queen : public ChessPiece {
public:
    Queen(glm::vec3 initialPosition, glm::vec3 pieceColor);
    void draw(Shader& shader, glm::mat4 model) override;

private:
    Cylinder cylinderPart;
    Cube cubePart;
    void drawCylinderPart(Shader& shader, glm::mat4 parentModel, glm::vec3 localPosition, glm::vec3 dimensions);
    void drawCubePart(Shader& shader, glm::mat4 parentModel, glm::vec3 localPosition, glm::vec3 dimensions);
};
