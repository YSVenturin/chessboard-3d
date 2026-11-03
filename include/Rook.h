#include "ChessPiece.h"
#include "Cube.h"
#include "Cylinder.h"

class Rook : public ChessPiece {
public:
    Rook(glm::vec3 initialPosition, glm::vec3 pieceColor);
    void draw(Shader& shader, glm::mat4 model) override;

private:
    Cube cubePart;
    Cylinder cylinderPart;
    void drawCubePart(Shader& shader,glm::mat4 parentModel,glm::vec3 localPosition,glm::vec3 dimensions);
    void drawCylinderPart(Shader& shader,glm::mat4 parentModel,glm::vec3 localPosition,glm::vec3 dimensions);
};
