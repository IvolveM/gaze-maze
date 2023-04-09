#include "Game.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Game::Game(int width, int height) {
    initGlfw();
    initShaders();

	glEnable(GL_DEPTH_TEST); // enable depth testing

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw FailedGLADInit();
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    stbi_set_flip_vertically_on_load(true); // before loading any image
}

Game::~Game() {
    glfwTerminate();
}

void Game::initGlfw() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    this->window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        throw FailedGLFWInit();
    }
    glfwMakeContextCurrent(window);
}

void Game::initShaders(){
    const char* vertShader = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main()
        {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
        }
    )";


    const char* fragShader = R"(
        #version 330 core

        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(1.0, 1.0, 1.0, 1.0);
        }
    )";

    this->shader = Shader(vertShader, fragShader);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Game::mainloop() {
    while(!glfwWindowShouldClose(window)) {
        processInput();
        render();
    }
}

void Game::render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // fills the screen with the color configured by glClearColor, and clears the depth buffer bit

    shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    shader.setMatrixFloat4("model", model);

    shader.setFloat3("ourColor", 1.0f, 1.0f, 0.4f);

    // glBindVertexArray(VAO);
    // glDrawArrays(GL_TRIANGLES, 0, 36);

    // check and call events and swap the buffers
    glfwPollEvents();
    glfwSwapBuffers(window);
}



void Game::processInput() {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);

    }
}