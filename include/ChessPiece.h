#pragma once
#include "Object.h"

class ChessPiece : public Object{
public:
    ChessPiece(glm::vec3 initialPosition, glm::vec3 pieceColor);
    void draw(Shader& shader, glm::mat4 model) override = 0;
    void setSelected(bool selected);

protected:
    glm::vec3 color;

private:
    glm::vec3 originalColor;
};
