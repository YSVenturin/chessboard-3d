#pragma once
#include "Cube.h"
#include "Shader.h"
#include <glm/glm.hpp>

class Chessboard {
public:
    Chessboard();
    void draw(Shader& shader, glm::mat4 model);

private:
    int boardSize;
    Cube whiteTile;
    Cube blackTile;
};
