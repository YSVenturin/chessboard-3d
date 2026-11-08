#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>

#include "Application.h"
#include "Chessboard.h"
#include "Shader.h"
#include "Camera.h"
#include "ChessSet.h"
#include "PostProcessor.h"

bool lbutton_down = false;
bool lbutton_click = false;
bool rbutton_click = false;

double clickX = 0.0;
double clickY = 0.0;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS && !lbutton_down) {
            lbutton_down = true;

            // save the cursor position when the button is pressed
            glfwGetCursorPos(window, &clickX, &clickY);
            lbutton_click = true;
        } else if (action == GLFW_RELEASE) {
            lbutton_down = false;
        }
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        rbutton_click = true;
        lbutton_click = false;
    }
}

// find the visible point under the mouse
bool getClickedPoint(GLFWwindow* window, double xpos, double ypos, const glm::mat4& view, const glm::mat4& projection, glm::vec3& point) {
    int width;
    int height;
    glfwGetWindowSize(window, &width, &height);

    int framebufferWidth;
    int framebufferHeight;
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

    if (width <= 0 || height <= 0 || framebufferWidth <= 0 || framebufferHeight <= 0) {
        return false;
    }

    // ignore click outside the window
    if (xpos < 0 || xpos >= width || ypos < 0 || ypos >= height) {
        return false;
    }

    // scale the cursor coordinates to match the framebuffer size
    int MOUSE_X = static_cast<int>(xpos * framebufferWidth / width);
    int MOUSE_Y = static_cast<int>(ypos * framebufferHeight / height);

    // glfw counts rows from the top but OpenGL counts from the bottom
    MOUSE_Y = framebufferHeight - 1 - MOUSE_Y;

    // read the depth of the visible surface at this pixel
    float depth = 1.0f;
    glReadPixels(MOUSE_X, MOUSE_Y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

    // ignore clicks on the background.
    if (depth >= 1.0f) {
        return false;
    }

    // use the center of the pixel and the depth we just read
    glm::vec3 screenPoint(MOUSE_X + 0.5f, MOUSE_Y + 0.5f, depth);
    glm::vec4 viewport(0, 0, framebufferWidth, framebufferHeight);

    // recover the world position using the matrices used to draw the scene
    point = glm::unProject(screenPoint, view, projection, viewport);
    return true;
}

int main() {
    Application app(1024, 768, "Chessboard3D");
    if (!app.init()) return -1;
    glfwSetMouseButtonCallback(app.getWindow(), mouse_button_callback);

    Chessboard chessboard;
    ChessSet chessSet;

    // Shader
    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    Shader postShader("shaders/postprocess_vertex.glsl", "shaders/postprocess_fragment.glsl");

    Camera camera(glm::vec3(7.0f, 8.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    PostProcessor postProcessor;
    int framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize(app.getWindow(), &framebufferWidth, &framebufferHeight);
    if (!postProcessor.init(framebufferWidth, framebufferHeight)) {
        std::cerr << "Não foi possível inicializar o framebuffer de pós-processamento.\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    bool resetKeyWasPressed = false;

    double previousTime = glfwGetTime();
    double currentTime = glfwGetTime();

    // main loop
    while (!glfwWindowShouldClose(app.getWindow())) {
        // Calculate the time difference to keep the cameraSpeed consistent between different computers
        currentTime = glfwGetTime();
        float timeDiff = static_cast<float>(currentTime - previousTime);
        previousTime = currentTime;

        camera.processInput(app.getWindow(), timeDiff);

        // Reset piece positions only once per key press (not every frame while R is held).
        bool resetKeyIsPressed = glfwGetKey(app.getWindow(), GLFW_KEY_R) == GLFW_PRESS;
        if (resetKeyIsPressed && !resetKeyWasPressed) {
            chessSet.resetPositions();
        }
        resetKeyWasPressed = resetKeyIsPressed;

        if (glfwGetKey(app.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(app.getWindow(), true);

        glfwGetFramebufferSize(app.getWindow(), &framebufferWidth, &framebufferHeight);
        if (framebufferWidth <= 0 || framebufferHeight <= 0) {
            glfwPollEvents();
            continue;
        }
        if (!postProcessor.resize(framebufferWidth, framebufferHeight)) {
            std::cerr << "Falha ao redimensionar o framebuffer.\n";
            break;
        }

        // Primeira passagem: renderiza a cena completa em um framebuffer off-screen.
        postProcessor.beginScene();
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.16f, 0.20f, 0.27f, 1.0f); // background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        const GLfloat backgroundObjectId[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        glClearBufferfv(GL_COLOR, 1, backgroundObjectId);

        shader.use();
        glm::mat4 model(1.0f);
        float aspectRatio = static_cast<float>(framebufferWidth) / static_cast<float>(framebufferHeight);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

        // View tile from an upper diagonal position
        glm::mat4 view = camera.getView();

        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.setVec3("viewPos", camera.getPosition());
        // Direção da superfície em direção à fonte de luz.
        shader.setVec3("lightDirection", glm::normalize(glm::vec3(-0.45f, 1.0f, 0.55f)));

        // Draw chessboard
        chessboard.draw(shader, model);
        // draw pieces
        chessSet.draw(shader, model);

        // Segunda passagem: compõe a imagem e desenha contornos nas fronteiras entre IDs distintos. Todas as primitivas de uma mesma peça têm o mesmo ID.
        postProcessor.render(postShader);

        // right button clear selection
        if (rbutton_click) {
            chessSet.clearSelection();
            rbutton_click = false;
        }

        // left button select and move piece
        if (lbutton_click) {
            glm::vec3 clickedPoint;
            glBindFramebuffer(GL_READ_FRAMEBUFFER, postProcessor.getFramebuffer());
            if (getClickedPoint(app.getWindow(), clickX, clickY, view, projection, clickedPoint)) {
                chessSet.handleClick(clickedPoint);
            }
            glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
            lbutton_click = false;
        }

        // Swap buffers and events
        glfwSwapBuffers(app.getWindow());
        glfwPollEvents();
    }

    return 0;
}
