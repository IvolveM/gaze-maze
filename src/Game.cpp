#include "Game.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Game::Game(int width, int height){
    initGlfw();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw FailedGLADInit();
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    stbi_set_flip_vertically_on_load(true); // before loading any image

	glEnable(GL_DEPTH_TEST); // enable depth testing
    glEnable(GL_MULTISAMPLE); // enable multisampling
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    initShaders();
    initTextures();

    // init shader matrices buffer
    glGenBuffers(1, &uboMatrices);
  
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(proj));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);  

    this->player = Player();

    this->maze = MazeLoader().loadMazeFromFile("../assets/maze.txt");
    
    this->ground = new Plane(glm::vec3{0.0f, -0.5f, 0.0f}, 100.0f, 1.0f);
}

Game::~Game() {
    glfwTerminate();
}

void Game::initGlfw() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4); // sampling hints
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
        layout (location = 0) in vec3 pos;
        layout (location = 1) in vec2 texCoord;

        layout (std140) uniform Matrices
        {
            mat4 projection;
            mat4 view;
        };


        out vec2 TexCoord;

        uniform mat4 model;

        void main()
        {
            gl_Position = projection * view * model * vec4(pos, 1.0);
            TexCoord = texCoord;
        }
    )";


    const char* fragShader = R"(
        #version 330 core
        out vec4 FragColor;

        in vec2 TexCoord;
        uniform sampler2D texture0;

        void main()
        {
            // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
            FragColor = texture(texture0, TexCoord);
        }
    )";

    const char* instanceShader = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec2 aTexCoord;
        layout (location = 2) in mat4 aInstanceMatrix;

        layout (std140) uniform Matrices
        {
            mat4 projection;
            mat4 view;
        };

        out vec2 TexCoord;

        void main()
        {
            TexCoord = aTexCoord;
            gl_Position = projection * view * aInstanceMatrix * vec4(aPos, 1.0f); 
        }
    )";

    ResourceManager::addShader("defaultShader", vertShader, fragShader).use().setBlockBinding("Matrices", 0);
    ResourceManager::addShader("instanceShader", instanceShader, fragShader).use().setBlockBinding("Matrices", 0);
}

void Game::initTextures(){
    ResourceManager::setTexture("defaultTexture", "../assets/textures/wall2.jpg");
    ResourceManager::setTexture("groundTexture", "../assets/textures/ground2.jpg");
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Game::mainloop() {
	float oldTime = 0.0f;
    while(!glfwWindowShouldClose(window)) {
        float newTime = glfwGetTime();
        this->dt = newTime - oldTime;
        oldTime = newTime;

        processInput();
        processEvents();

        glm::mat4 view = player.getView();
        glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        render();
    }
}

void Game::render() {
    glClearColor(37.0f/255.0f, 124.0f/255.0f, 190.0f/255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // fills the screen with the color configured by glClearColor, and clears the depth buffer bit

    // handle render calls here
    maze->draw();
    // for (Cube* cube : this->mazeCubes) {
    //     cube->draw();
    // }
    ground->draw();

    // check and call events and swap the buffers
    glfwPollEvents();
    glfwSwapBuffers(window);
}



void Game::processInput() {
    handleMouse();
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        player.handleKeyInput(Player::InputEvent::FORWARDS);
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        player.handleKeyInput(Player::InputEvent::BACKWARDS);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        player.handleKeyInput(Player::InputEvent::LEFT);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        player.handleKeyInput(Player::InputEvent::RIGHT);
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        player.handleKeyInput(Player::InputEvent::JUMP);
    }
}

void Game::processEvents()
{
    player.doCollisions(*(this->maze));
    player.update(this->dt);
}

void Game::handleMouse()
{
    GLdouble xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    player.setDirectionByMouse((float)xPos, (float)yPos);
}