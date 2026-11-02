#include "ChessPiece.h"
#include "Cube.h"

class Rook : public ChessPiece {
public:
    Rook(glm::vec3 initialPosition, glm::vec3 pieceColor);
    void draw(Shader& shader, glm::mat4 model);

private:
    Cube cubePart;
    void drawCubePart(Shader& shader, glm::mat4 parentModel, glm::vec3 localPosition, glm::vec3 dimensions);
};
