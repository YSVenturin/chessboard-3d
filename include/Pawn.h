#pragma once
#include "ChessPiece.h"
#include "Cylinder.h"

class Pawn : public ChessPiece {
public:
    Pawn(glm::vec3 initialPosition, glm::vec3 pieceColor);
    void draw(Shader& shader, glm::mat4 model) override;

private:
    Cylinder cylinderPart;
    void drawCylinderPart(Shader& shader, glm::mat4 parentModel, glm::vec3 localPosition, glm::vec3 dimensions);
};
