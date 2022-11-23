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

const int g_windowSizeX = 13 * 16;
const int g_windowSizeY = 14 * 16;

glm::ivec2 g_windowSize( g_windowSizeX, g_windowSizeY );
Game g_game( g_windowSize );

void onWindowSizeChangedStatic(GLFWwindow* window, int width, int height){
    g_windowSize.x = width;
    g_windowSize.y = height;
    // const float aspect_ratio = 13.0f /14.0f;
    const float aspect_ratio = static_cast< float >( g_game.currentLevelWidth() ) / static_cast< float > ( g_game.currentLevelHeight() );
    GLint viewPortWidth = g_windowSize.x;
    GLint viewPortHeight = g_windowSize.y;
    GLint viewPortLeftOffset = 0;
    GLint viewPortBottomOffset = 0;

    if( static_cast<float>( g_windowSize.x ) / g_windowSize.y > aspect_ratio ){
        viewPortWidth = static_cast<int>( g_windowSize.y * aspect_ratio );
        viewPortLeftOffset = static_cast<int>( (g_windowSize.x - viewPortWidth) * 0.5f );
    }else{
        viewPortHeight = static_cast< int >( g_windowSize.x / aspect_ratio );
        viewPortBottomOffset = static_cast<int>((g_windowSize.y - viewPortHeight) * 0.5f);
    }

    glViewport( viewPortLeftOffset, viewPortBottomOffset, viewPortWidth, viewPortHeight);
}

bool isEagle = false;

void onKeyPressed(GLFWwindow* pWnd, int keyCode, int scanCode, int action, int mode) {
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