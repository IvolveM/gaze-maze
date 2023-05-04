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
    // glEnable(GL_MULTISAMPLE); // enable multisampling
    glfwSwapInterval( 0 ); // disable vsync
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    initShaders();
    initTextures();

    // init shader matrices buffer
    glGenBuffers(1, &uboMatrices);
  
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4) + sizeof(glm::vec3), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4) + sizeof(glm::vec3));

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(proj));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);  

    this->player = Player();

    // this->maze = MazeLoader().loadMazeFromFile("../assets/maze.txt");
    this->maze = MazeGenerator().getMaze();
    
    this->ground = new Plane(glm::vec3{0.0f, -0.5f, 0.0f}, 100.0f, 1.0f);

    // this->model = new Model("../assets/meshes/backpack/backpack.obj");
}

Game::~Game() {
    glfwTerminate();
}

void Game::initGlfw() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_SAMPLES, 4); // sampling hints
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
            vec3 cameraPos;
        };

        out vec2 TexCoord;
        out vec3 CameraPos;

        uniform mat4 model;

        void main()
        {
            CameraPos = cameraPos;
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
        // uniform sampler2D texture_diffuse1;
        // uniform sampler2D texture_diffuse2;
        // uniform sampler2D texture_diffuse3;
        // uniform sampler2D texture_specular1;
        // uniform sampler2D texture_specular2;

    
    const char* cubeVertShader = R"(
        #version 330 core
        layout (location = 0) in vec3 pos;
        layout (location = 1) in vec3 aNormal;
        layout (location = 2) in vec2 texCoord;

        layout (std140) uniform Matrices
        {
            mat4 projection;
            mat4 view;
            vec3 cameraPos;
        };

        out vec2 TexCoord;
        out vec3 Normal;
        out vec3 FragPos;
        out vec3 CameraPos;

        uniform mat4 model;

        void main()
        {
            CameraPos = cameraPos;
            TexCoord = texCoord;
            Normal = mat3(transpose(inverse(model))) * aNormal;
            FragPos = vec3(model * vec4(pos, 1.0));

            gl_Position = projection * view * model * vec4(pos, 1.0);
        }
    )";

    const char* instanceShader = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aNormalCoord;
        layout (location = 2) in vec2 aTexCoord;
        layout (location = 3) in mat4 aInstanceMatrix;

        layout (std140) uniform Matrices
        {
            mat4 projection;
            mat4 view;
            vec3 cameraPos;
        };

        out vec3 CameraPos;
        out vec2 TexCoord;
        out vec3 Normal;
        out vec3 FragPos;

        void main()
        {
            CameraPos = cameraPos;
            TexCoord = aTexCoord;
            Normal = mat3(transpose(inverse(aInstanceMatrix))) * aNormalCoord;
            FragPos = vec3(aInstanceMatrix * vec4(aPos, 1.0));

            gl_Position = projection * view * vec4(FragPos, 1.0f); 
        }
    )";

    const char* cubeFragShader = R"(
        #version 330 core
        out vec4 FragColor;

        in vec2 TexCoord;
        in vec3 Normal;
        in vec3 FragPos;
        in vec3 CameraPos;

        uniform sampler2D texture0;

        void main()
        {
            vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
            vec3 lightPos = vec3(1.2f, 2.0f, 2.0f);

            // ambient
            float ambientStrength = 0.9;
            vec3 ambient = ambientStrength * lightColor;

            // diffuse
            vec3 norm = normalize(Normal);
            vec3 lightDir = normalize(lightPos - FragPos);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = diff * lightColor;

            // specular
            float specularStrength = 0.5;
            vec3 viewDir = normalize(CameraPos - FragPos);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // 32 = shininess
            vec3 specular = specularStrength * spec * lightColor;

            vec4 textureColor = texture(texture0, TexCoord);
            vec3 result = (ambient + diffuse + specular) * textureColor.xyz;
            FragColor = vec4(result, 1.0f);
        }
    )";

    ResourceManager::addShader("defaultShader", vertShader, fragShader).use().setBlockBinding("Matrices", 0);
    ResourceManager::addShader("cubeShader", cubeVertShader, cubeFragShader).use().setBlockBinding("Matrices", 0);
    ResourceManager::addShader("instanceShader", instanceShader, cubeFragShader).use().setBlockBinding("Matrices", 0);
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
        float fps = 1/dt;
        // std::cout<< "FPS: " << fps << std::endl;

        processInput();
        processEvents();

        glm::mat4 view = player.getView();
        glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        glm::vec3 viewPos = player.getPosition();
        glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
        glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(glm::vec3), glm::value_ptr(viewPos));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        render();
    }
}

void Game::render() {
    glClearColor(37.0f/255.0f, 124.0f/255.0f, 190.0f/255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // fills the screen with the color configured by glClearColor, and clears the depth buffer bit

    // handle render calls here
    maze->draw();
    ground->draw();
    // model->draw();

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
    player.update(this->dt);
    player.doCollisions(this->maze->getMesh(), dt);
}

void Game::handleMouse()
{
    GLdouble xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    player.setDirectionByMouse((float)xPos, (float)yPos);
}