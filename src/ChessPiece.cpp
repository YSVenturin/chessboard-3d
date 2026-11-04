#include "ChessPiece.h"

ChessPiece::ChessPiece(glm::vec3 initialPosition, glm::vec3 pieceColor) {
    position = initialPosition;
    color = pieceColor;
    originalColor = pieceColor;
}

void ChessPiece::setSelected(bool selected) {
    if (selected) {
        color = glm::vec3(1.0f, 0.65f, 0.1f);
    } else {
        color = originalColor;
    }
}
