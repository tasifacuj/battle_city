#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

#include "renderer/ShaderProgram.hpp"

#include "resources/ResourceManager.hpp"

int g_windowSizeX = 640;
int g_windowSizeY = 480;

const char* vertexShader = R"(
#version 460
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;
out vec3 color;

void main(){
    color = vertex_color;
    gl_Position = vec4( vertex_position, 1.0 );
}
)";

const char* fragmentShader = R"(
#version 460

in vec3 color;
out vec4 frag_color;

void main(){
    frag_color = vec4( color, 1.0 );
}
)";

GLfloat point[] = {
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
};

GLfloat color[] = {
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 1.0f,
};

void onWindowSizeChangedStatic(GLFWwindow* window, int width, int height){
    g_windowSizeX = width;
    g_windowSizeY = height;
    glViewport(0, 0, g_windowSizeX, g_windowSizeY);
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
        auto programPtr = resourceManager.loadShaders( "main", "res/shaders/vertex.txt", "res/shaders/fragment.txt" );

        if( !programPtr ){
            return -1;
        }

        resourceManager.loadTexture( "map", "res/textures/map_8x8.png" );
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


        // bind data to shader
        GLuint vao;
        glGenVertexArrays( 1, &vao );
        glBindVertexArray( vao );

        glEnableVertexAttribArray(0);
        glBindBuffer( GL_ARRAY_BUFFER, points_vbo );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( float ) * 3, nullptr );

        glEnableVertexAttribArray(1);
        glBindBuffer( GL_ARRAY_BUFFER, color_vbo );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( float ) * 3, nullptr );

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);
            programPtr->use();
            glBindVertexArray( vao );
            glDrawArrays( GL_TRIANGLES, 0, 3 );
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}