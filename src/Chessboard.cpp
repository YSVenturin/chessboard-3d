#include "Chessboard.h"

Chessboard::Chessboard(){
    boardSize = 8;
    whiteTile.scale = glm::vec3(1.0f, 0.15f, 1.0f);
    blackTile.scale = glm::vec3(1.0f, 0.15f, 1.0f);
}

void Chessboard::draw(Shader& shader, glm::mat4 model){
    float centerOffset = (boardSize - 1) / 2.0f; // 3.5f when boardSize = 8

    for (int row = 0; row < boardSize; row++){
        for (int col = 0; col < boardSize; col++){
            float x = col - centerOffset;
            float z = row - centerOffset;

            glm::vec3 tilePosition(x, 0.0f, z);

            if ((row + col) % 2 == 0){
                whiteTile.position = tilePosition;
                shader.setVec3("objectColor", glm::vec3(0.9f, 0.9f, 0.9f));
                whiteTile.draw(shader, model);
            } else {
                blackTile.position = tilePosition;
                shader.setVec3("objectColor", glm::vec3(0.15f, 0.15f, 0.15f));
                blackTile.draw(shader, model);
            }
        }
    }
}
