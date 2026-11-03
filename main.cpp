#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Application.h"
#include "Chessboard.h"
#include "Shader.h"
#include "Camera.h"
#include "Rook.h"

int main() {
    Application app(1024, 768, "Chessboard3D");
    if (!app.init()) return -1;

    Chessboard chessboard;

    Rook whiteRook(glm::vec3(-3.5f, 0.075f, 3.5f), glm::vec3(0.9f, 0.9f, 0.9f));
    Rook blackRook(glm::vec3(-3.5f, 0.075f, -3.5f), glm::vec3(0.1f, 0.1f, 0.1f));

    // Shader
    Shader shader("vertex.glsl", "fragment.glsl");
    shader.use();

    Camera camera(glm::vec3(7.0f, 8.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    // turn on depth test
    glEnable(GL_DEPTH_TEST);

    double previousTime = glfwGetTime();
    double currentTime = glfwGetTime();

    // Main Loop
    while (!glfwWindowShouldClose(app.getWindow())) {
        // Calculate the time difference to keep the cameraSpeed consistent between different computers
        currentTime = glfwGetTime();
        float timeDiff = static_cast<float>(currentTime - previousTime);
        previousTime = currentTime;

        camera.processInput(app.getWindow(), timeDiff);

        if (glfwGetKey(app.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(app.getWindow(), true);

        glClearColor(0.7f, 0.5f, 0.1f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glm::mat4 model = glm::mat4(1.0f);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        // View tile from an upper diagonal position.
        glm::mat4 view = camera.getView();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        // Draw chessboard.
        chessboard.draw(shader, model);

        // draw test rook
        whiteRook.draw(shader, model);
        blackRook.draw(shader, model);

        // Swap buffers e eventos
        glfwSwapBuffers(app.getWindow());
        glfwPollEvents();
    }

    return 0;
}
