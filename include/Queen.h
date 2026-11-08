#pragma once
#include "ChessPiece.h"
#include "Cylinder.h"
#include "Pyramid.h"

class Queen : public ChessPiece {
public:
    Queen(glm::vec3 initialPosition, glm::vec3 pieceColor);
    void draw(Shader& shader, glm::mat4 model) override;

private:
    Cylinder cylinderPart;
    Pyramid pyramidPart;

    void drawCylinderPart(Shader& shader, glm::mat4 parentModel,
                          glm::vec3 localPosition, glm::vec3 dimensions);
    void drawPyramidPart(Shader& shader, glm::mat4 parentModel,
                         glm::vec3 localPosition, glm::vec3 dimensions);
};
