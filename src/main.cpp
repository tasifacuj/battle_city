#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

#include "renderer/ShaderProgram.hpp"
#include "renderer/Texture2D.hpp"
#include "renderer/Sprite.hpp"

#include "resources/ResourceManager.hpp"

// glm
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

const int g_windowSizeX = 640;
const int g_windowSizeY = 480;

glm::ivec2 g_windowSize( g_windowSizeX, g_windowSizeY );


GLfloat point[] = {
    0.0f, 50.f, 0.0f,
    50.5f, -50.5f, 0.0f,
    -50.5f, -50.5f, 0.0f,
};

GLfloat color[] = {
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 1.0f,
};

GLfloat texCoords[] = {
    0.5f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
};

void onWindowSizeChangedStatic(GLFWwindow* window, int width, int height){
    g_windowSize.x = width;
    g_windowSize.y = height;
    glViewport(0, 0, g_windowSize.x, g_windowSize.y);
}

void onKeyPressed(GLFWwindow* pWnd, int keyCode, int scanCode, int action, int mode) {
    if (keyCode == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(pWnd, GL_TRUE);
    }
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
    glClearColor( 0, 1, 0, 1 );
    
    {
        resources::ResourceManager resourceManager( argv[0] );
        auto programPtr = resourceManager.loadShaders( "default", "res/shaders/vertex.txt", "res/shaders/fragment.txt" );

        if( !programPtr ){
            return -1;
        }

        auto spriteProgramPtr = resourceManager.loadShaders( "sprites_shader", "res/shaders/sprite.vert", "res/shaders/sprite.frag" );

        if( !spriteProgramPtr ){
            return -1;
        }

        auto texPtr = resourceManager.loadTexture( "default", "res/textures/map_16x16.png" );
        std::vector<std::string> subNames{
            "block",
            "topBlock",
            "bottomBlock",
            "leftBlock",
            "rightBlock",
            "topLeftBlock",
            "topRightBlock",
            "bottomLeftBlock",
            "bottomRightBlock",
            "concrete"
        };
        auto texAtlasPtr = resourceManager.loadTextureAtlas( "TexAtlas", "res/textures/map_16x16_.png", 16, 16, subNames );

        auto spritePtr = resourceManager.loadSprite( "default", "TexAtlas", "sprites_shader", 100 ,100, "concrete" );

        if( !spritePtr ){
            std::cout << "Failed to load defaut sprite"  << std::endl;
            return -1;
        }

        spritePtr->setPosition( glm::vec2( 190, 100 ) );

        // create vertex data
        GLuint points_vbo;
        glGenBuffers( 1, &points_vbo );
        glBindBuffer( GL_ARRAY_BUFFER, points_vbo );
        glBufferData( GL_ARRAY_BUFFER, sizeof( point ), point, GL_STATIC_DRAW );

        // create color data
        GLuint color_vbo;
        glGenBuffers( 1, &color_vbo );
        glBindBuffer( GL_ARRAY_BUFFER, color_vbo );
        glBufferData( GL_ARRAY_BUFFER, sizeof( color ), color, GL_STATIC_DRAW );

        // textures vbo
        GLuint tex_vbo;
        glGenBuffers( 1, &tex_vbo );
        glBindBuffer( GL_ARRAY_BUFFER, tex_vbo );
        glBufferData( GL_ARRAY_BUFFER, sizeof( texCoords ), texCoords, GL_STATIC_DRAW );


        // bind data to shader
        GLuint vao;
        glGenVertexArrays( 1, &vao );
        glBindVertexArray( vao );

        glEnableVertexAttribArray(0);
        glBindBuffer( GL_ARRAY_BUFFER, points_vbo );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

        glEnableVertexAttribArray(1);
        glBindBuffer( GL_ARRAY_BUFFER, color_vbo );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

        glEnableVertexAttribArray( 2 );
        glBindBuffer( GL_ARRAY_BUFFER, tex_vbo );
        glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 0, nullptr );

        programPtr->use();
            programPtr->setInt( "sampler", 0 );// use texture loaded into GL_TEXTURE_0
            
            glm::mat4 model( 1.0f );
            model = glm::translate( model, glm::vec3( 100.0f, 200.0f, 0.0f ) );
            glm::mat4 model2 = glm::translate( glm::mat4( 1.0f ), glm::vec3( 590.0f, 50.0f, 0.0f ) );

            glm::mat4 projMatrix = glm::ortho( 0.0f, float( g_windowSize.x ), 0.0f, float( g_windowSize.y ), -100.0f, 100.0f );
            programPtr->setMatrix4( "projection", projMatrix );

        spriteProgramPtr->use();
            spriteProgramPtr->setInt( "sampler", 0 );
            spriteProgramPtr->setMatrix4( "projection", projMatrix );

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);
            programPtr->use();
            
            glBindVertexArray( vao );
                texPtr->bind();
                programPtr->setMatrix4( "model", model );
                glDrawArrays( GL_TRIANGLES, 0, 3 );// first triangle

                programPtr->setMatrix4( "model", model2 );
                glDrawArrays( GL_TRIANGLES, 0, 3 );// second triangle
            glBindVertexArray( 0 );

            spritePtr->render();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}