#include "Chessboard.h"

Chessboard::Chessboard(){
    boardSize = 8;
    whiteTile.scale = glm::vec3(1.0f, 0.15f, 1.0f);
    blackTile.scale = glm::vec3(1.0f, 0.15f, 1.0f);
}

void Chessboard::draw(Shader& shader, glm::mat4 model){
    float centerOffset = 3.5f;

    for (int row = 0; row < boardSize; row++){
        for (int col = 0; col < boardSize; col++){
            float x = col - centerOffset;
            float z = row - centerOffset;

            glm::vec3 tilePosition(x, 0.0f, z);

            // O tabuleiro usa o ID zero: o pós-processamento só contorna peças
            // Não vejo necessidade de contornar o tabuleiro
            shader.setInt("objectId", 0);
            shader.setFloat("materialShininess", 18.0f);
            shader.setFloat("specularStrength", 0.10f);

            if ((row + col) % 2 == 0){
                whiteTile.position = tilePosition;
                shader.setVec3("objectColor", glm::vec3(0.78f, 0.80f, 0.82f));
                whiteTile.draw(shader, model);
            } else {
                blackTile.position = tilePosition;
                shader.setVec3("objectColor", glm::vec3(0.075f, 0.095f, 0.13f));
                blackTile.draw(shader, model);
            }
        }
    }
}
