#pragma once
#include <vector>

#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

class ChessSet {
public:
    ChessSet();
    void draw(Shader& shader, glm::mat4 model);
    void handleClick(const glm::vec3& point);
    void clearSelection();
    void resetPositions();

private:
    std::vector<Pawn> pawns;
    std::vector<Rook> rooks;
    std::vector<Knight> knights;
    std::vector<Bishop> bishops;
    std::vector<Queen> queens;
    std::vector<King> kings;

    void createSide(bool isWhite, glm::vec3 pieceColor, float boardHeight);

    ChessPiece* selectedPiece = nullptr;
    ChessPiece* findPiece(float x, float z);
};
