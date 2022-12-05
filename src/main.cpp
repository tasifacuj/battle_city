// glad
#include "glad/glad.h"

// glfw
#include <GLFW/glfw3.h>

// std
#include <iostream>
#include <chrono>

#include "renderer/ShaderProgram.hpp"
#include "renderer/Texture2D.hpp"
#include "renderer/Sprite.hpp"
#include "renderer/Renderer.hpp"
#include "resources/ResourceManager.hpp"
#include "game/Game.hpp"
#include "phys/PhysicsEngine.hpp"

// glm
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

const int g_windowSizeX = 16;
const int g_windowSizeY = 15;
const int SCALE         = 3;
const int BLOCK_SIZE    = 16;

glm::ivec2 g_windowSize( SCALE * BLOCK_SIZE * g_windowSizeX, SCALE * BLOCK_SIZE * g_windowSizeY );
Game g_game( g_windowSize );

void onWindowSizeChangedStatic(GLFWwindow* window, int width, int height){
    g_windowSize.x = width;
    g_windowSize.y = height;
    g_game.setWinfowSize( g_windowSize );
}

bool isEagle = false;

void onKeyPressed(GLFWwindow* pWnd, int keyCode, int scanCode, int action, int /*mode*/) {
    if (keyCode == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(pWnd, GL_TRUE);
    }

    g_game.setKey( keyCode, action );
}

int main( int argc, char** argv ){
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 6 );
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(window, onWindowSizeChangedStatic);
    glfwSetKeyCallback(window, onKeyPressed);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if( !gladLoadGL() ){
        std::cout << "Failed to load glad" << std::endl;
        return -1;
    }

    std::cout << "Opengl " <<  GLVersion.major << "." << GLVersion.minor << std::endl;
    std::cout << "Renerer: " << glGetString(GL_RENDERER) << std::endl;
    renderer::Renderer::setClearColor( 0, 0, 0, 1 );
    renderer::Renderer::setDepthTest( true );
    
    {
        resources::ResourceManager& resourceManager = resources::ResourceManager::getInstance();
        resourceManager.initialize( argv[0] );
        
        if( !g_game.initialize() ){
            std::cout << "Failed to initialize game" << std::endl;
            return -1;
        }
        
        phys::PhysicsEngine& ph = phys::PhysicsEngine::getInstance();
        ph.init();
        glfwSetWindowSize( window, static_cast<int>(3*g_game.currentLevelWidth()), static_cast<int>(3*g_game.currentLevelHeight()) );
        auto lastTime = std::chrono::high_resolution_clock::now();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)){
            /* Render here */
            renderer::Renderer::clear();
            
            auto now = std::chrono::high_resolution_clock::now();
            double duration = std::chrono::duration< double, std::milli >( now - lastTime ).count();
            lastTime = now;

            g_game.update( duration );
            ph.update( duration );
            g_game.render();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        resourceManager.free();
    }

    glfwTerminate();
    return 0;
}