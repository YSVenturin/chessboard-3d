#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Application.h"
#include "Chessboard.h"
#include "Shader.h"

int main() {
    Application app(1024, 768, "Chessboard3D");
    if (!app.init()) return -1;

    Chessboard chessboard;

    // Shader
    Shader shader("vertex.glsl", "fragment.glsl");
    shader.use();

    // Define the camera position, target, and up direction.
    glm::vec3 cameraPosition(7.0f, 8.0f, 10.0f);
    glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

    // turn on depth test
    glEnable(GL_DEPTH_TEST);

    // Main Loop
    while (!glfwWindowShouldClose(app.getWindow())) {
        if (glfwGetKey(app.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(app.getWindow(), true);

        //glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClearColor(0.7f, 0.5f, 0.1f, 1.0f);
        //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glm::mat4 model = glm::mat4(1.0f);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                                800.0f / 600.0f,
                                                0.1f, 100.0f);
        // View tile from an upper diagonal position.
        glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        // Draw chessboard.
        chessboard.draw(shader, model);

        // Swap buffers e eventos
        glfwSwapBuffers(app.getWindow());
        glfwPollEvents();
    }

    return 0;
}
