#include "ChessSet.h"

float boardHeight = 0.075f;

ChessSet::ChessSet() {
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

ChessPiece* ChessSet::findPiece(float x, float z) {
    // search for piece at the center of the clicked tile
    for (Pawn& pawn : pawns) {
        if (pawn.position.x == x && pawn.position.z == z) {
            return &pawn;
        }
    }

    for (Rook& rook : rooks) {
        if (rook.position.x == x && rook.position.z == z) {
            return &rook;
        }
    }

    for (Knight& knight : knights) {
        if (knight.position.x == x && knight.position.z == z) {
            return &knight;
        }
    }

    for (Bishop& bishop : bishops) {
        if (bishop.position.x == x && bishop.position.z == z) {
            return &bishop;
        }
    }

    for (Queen& queen : queens) {
        if (queen.position.x == x && queen.position.z == z) {
            return &queen;
        }
    }

    for (King& king : kings) {
        if (king.position.x == x && king.position.z == z) {
            return &king;
        }
    }

    return nullptr;
}

void ChessSet::clearSelection() {
    if (selectedPiece != nullptr) {
        selectedPiece->setSelected(false);
        selectedPiece = nullptr;
    }
}

void ChessSet::handleClick(const glm::vec3& point) {
    // ignores click outside chessboard limit
    if (point.x < -4.0f || point.x >= 4.0f || point.z < -4.0f || point.z >= 4.0f) {
        return;
    }

    // ignores click if its bellow the board height
    if (point.y < boardHeight) {
        return;
    }

    // convert the clicked point to a round true index
    // the centered board goes from -4 to +4, thats why we sum 4, so the index goes from 0 to 7
    int column = static_cast<int>(point.x + 4.0f);
    int row = static_cast<int>(point.z + 4.0f);

    // a tile has 1x1 size, so 0.5 is the center
    // the first tile center is on -3.5 x -3.5, so we subtract this from to discover the center
    float centerX = column - 3.5f;
    float centerZ = row - 3.5f;

    ChessPiece* clickedPiece = findPiece(centerX, centerZ);
    // if the user clicked a piece or a tile
    if (clickedPiece != nullptr) {
        clearSelection();
        selectedPiece = clickedPiece;
        selectedPiece->setSelected(true);
        return;
    }

    // if a piece is selected and the user clicked on a tile
    if (selectedPiece != nullptr) {
        // move the piece to the empty tile
        selectedPiece->position.x = centerX;
        selectedPiece->position.z = centerZ;
        clearSelection();
    }
}
