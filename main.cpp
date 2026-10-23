#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Shader.h>
#include <Application.h>
#include <Cube.h>
#include <Texture.h>
#include <iostream>

int main() {
    Application app(1024, 768, "Chessboard3D");
    if (!app.init()) return -1;

    // Shader
    Shader shader("vertex.glsl", "fragment.glsl");
    shader.use();

    // Load texture
    Texture tex1("pedra-28.jpg");
    Texture tex2("opengl.png");  // logo OpenGL com alpha

    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    Cube cube(glm::vec3(0.0f));

    // Shape the cube into a chessboard tile.
    cube.scale = glm::vec3(1.0f, 0.15f, 1.0f);

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
        // View the tile from an elevated diagonal position.
        glm::mat4 view = glm::lookAt(
            glm::vec3(2.0f, 2.0f, 3.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        // Bind textures
        tex1.bind(0);
        tex2.bind(1);

        cube.draw(shader, model);

        // Swap buffers e eventos
        glfwSwapBuffers(app.getWindow());
        glfwPollEvents();
    }

    return 0;
}
