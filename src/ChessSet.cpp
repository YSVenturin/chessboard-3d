#include "ChessSet.h"

float boardHeight = 0.075f;

ChessSet::ChessSet() {
    createSide(true, glm::vec3(0.90f, 0.87f, 0.79f), boardHeight);
    createSide(false, glm::vec3(0.19f, 0.22f, 0.28f), boardHeight);
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
    
    int nextObjectId = 1;
    shader.setFloat("materialShininess", 52.0f);
    shader.setFloat("specularStrength", 0.28f);

    for (Pawn& pawn : pawns) {
        shader.setInt("objectId", nextObjectId++);
        pawn.draw(shader, model);
    }
    for (Rook& rook : rooks) {
        shader.setInt("objectId", nextObjectId++);
        rook.draw(shader, model);
    }
    for (Knight& knight : knights) {
        shader.setInt("objectId", nextObjectId++);
        knight.draw(shader, model);
    }
    for (Bishop& bishop : bishops) {
        shader.setInt("objectId", nextObjectId++);
        bishop.draw(shader, model);
    }
    for (Queen& queen : queens) {
        shader.setInt("objectId", nextObjectId++);
        queen.draw(shader, model);
    }
    for (King& king : kings) {
        shader.setInt("objectId", nextObjectId++);
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

void ChessSet::resetPositions() {
    // Deselect the current piece before restoring the initial board layout.
    clearSelection();

    // Pawns: the first 8 belong to White and the next 8 to Black.
    for (std::size_t i = 0; i < pawns.size(); ++i) {
        const bool isWhite = i < 8;
        const int column = static_cast<int>(i % 8);
        const float pawnRowZ = isWhite ? 2.5f : -2.5f;
        pawns[i].position = glm::vec3(-3.5f + column, boardHeight, pawnRowZ);
    }

    // The remaining pieces are stored in pairs: White first, then Black.
    for (int side = 0; side < 2; ++side) {
        const bool isWhite = (side == 0);
        const float backRowZ = isWhite ? 3.5f : -3.5f;
        const std::size_t first = static_cast<std::size_t>(side * 2);

        rooks[first].position = glm::vec3(-3.5f, boardHeight, backRowZ);
        rooks[first + 1].position = glm::vec3(3.5f, boardHeight, backRowZ);

        knights[first].position = glm::vec3(-2.5f, boardHeight, backRowZ);
        knights[first + 1].position = glm::vec3(2.5f, boardHeight, backRowZ);
        knights[first].rotation = glm::vec3(0.0f, 1.0f, 0.0f);
        knights[first + 1].rotation = glm::vec3(0.0f, 1.0f, 0.0f);
        knights[first].angle = isWhite ? 180.0f : 0.0f;
        knights[first + 1].angle = isWhite ? 180.0f : 0.0f;

        bishops[first].position = glm::vec3(-1.5f, boardHeight, backRowZ);
        bishops[first + 1].position = glm::vec3(1.5f, boardHeight, backRowZ);

        queens[side].position = glm::vec3(-0.5f, boardHeight, backRowZ);
        kings[side].position = glm::vec3(0.5f, boardHeight, backRowZ);
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
