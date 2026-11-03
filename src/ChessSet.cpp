#include "ChessSet.h"

ChessSet::ChessSet() {
    float boardHeight = 0.075f;

    createSide(true, glm::vec3(0.9f, 0.9f, 0.9f), boardHeight);
    createSide(false, glm::vec3(0.15f, 0.15f, 0.15f), boardHeight);
}

void ChessSet::createSide(bool isWhite, glm::vec3 pieceColor, float boardHeight) {
    float backRowZ;
    float pawnRowZ;
    float knightAngle;

    if (isWhite) {
        backRowZ = 3.5f;
        pawnRowZ = 2.5f;
        knightAngle = 180.0f;
    } else {
        backRowZ = -3.5f;
        pawnRowZ = -2.5f;
        knightAngle = 0.0f;
    }

    // Pawns
    for (int column = 0; column < 8; column++) {
        float x = -3.5f + column;
        pawns.emplace_back(glm::vec3(x, boardHeight, pawnRowZ), pieceColor);
    }

    // Rooks
    rooks.emplace_back(glm::vec3(-3.5f, boardHeight, backRowZ), pieceColor);
    rooks.emplace_back(glm::vec3(3.5f, boardHeight, backRowZ), pieceColor);

    // Knights
    knights.emplace_back(glm::vec3(-2.5f, boardHeight, backRowZ), pieceColor);
    knights.back().rotation = glm::vec3(0.0f, 1.0f, 0.0f);
    knights.back().angle = knightAngle;

    knights.emplace_back(glm::vec3(2.5f, boardHeight, backRowZ),pieceColor);
    knights.back().rotation = glm::vec3(0.0f, 1.0f, 0.0f);
    knights.back().angle = knightAngle;

    // Bishops
    bishops.emplace_back(glm::vec3(-1.5f, boardHeight, backRowZ), pieceColor);
    bishops.emplace_back(glm::vec3(1.5f, boardHeight, backRowZ), pieceColor);

    // Queen
    queens.emplace_back(glm::vec3(-0.5f, boardHeight, backRowZ), pieceColor);

    // King
    kings.emplace_back(glm::vec3(0.5f, boardHeight, backRowZ), pieceColor);
}

void ChessSet::draw(Shader& shader, glm::mat4 model) {
    for (Pawn& pawn : pawns) {
        pawn.draw(shader, model);
    }

    for (Rook& rook : rooks) {
        rook.draw(shader, model);
    }

    for (Knight& knight : knights) {
        knight.draw(shader, model);
    }

    for (Bishop& bishop : bishops) {
        bishop.draw(shader, model);
    }

    for (Queen& queen : queens) {
        queen.draw(shader, model);
    }

    for (King& king : kings) {
        king.draw(shader, model);
    }
}
