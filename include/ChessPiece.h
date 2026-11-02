#include "Object.h"

class ChessPiece : public Object{
public:
    ChessPiece(glm::vec3 initialPosition, glm::vec3 pieceColor);
    void draw(Shader& shader, glm::mat4 model) override = 0;

protected:
    glm::vec3 color;
};
