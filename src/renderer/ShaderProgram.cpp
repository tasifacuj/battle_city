#include "ShaderProgram.hpp"

// std
#include <iostream>

namespace renderer{

ShaderProgram::ShaderProgram( std::string const& vertexShader, std::string const& fragShader ){
    GLuint vertexShaderId;
    
    if( !createShader( vertexShader, GL_VERTEX_SHADER, vertexShaderId ) ){
        glDeleteShader( vertexShaderId );
        return;
    }

    GLuint fragmentShaderId;
    
    if( !createShader( fragShader, GL_FRAGMENT_SHADER, fragmentShaderId ) ){
        glDeleteShader( fragmentShaderId );
        return;
    }

    id_ = glCreateProgram();
    glAttachShader( id_, vertexShaderId );
    glAttachShader( id_, fragmentShaderId );
    glLinkProgram( id_ );

    GLint linkStatus;
    glGetProgramiv( id_, GL_LINK_STATUS, &linkStatus );

    if( linkStatus == GL_FALSE ){
        static const int logLength = 1024;
        GLchar logMessage[ logLength ];
        glGetShaderInfoLog(id_, logLength, nullptr, logMessage);
        std::cout << " The linker returned: " << std::endl << std::endl << logMessage << std::endl;
    }else{
        isCompiled_ = true;
    }

    glDeleteShader( vertexShaderId );
    glDeleteShader( fragmentShaderId );
}

ShaderProgram::~ShaderProgram(){
    glDeleteProgram( id_ );
}

void ShaderProgram::use(){
    glUseProgram( id_ );
}

bool ShaderProgram::createShader( std::string const& shaderText, GLenum type, GLuint& shaderId ){
    shaderId = glCreateShader( type );
    const char* data = shaderText.data();
    glShaderSource( shaderId, 1, &data, nullptr );
    glCompileShader( shaderId );

    GLint compilationStatus;
    glGetShaderiv( shaderId, GL_COMPILE_STATUS, &compilationStatus );

    if( compilationStatus == GL_FALSE ){
        static const int logLength = 1024;
        GLchar logMessage[ logLength ];
        glGetShaderInfoLog(shaderId, logLength, nullptr, logMessage);
        std::cout << " The compiler returned: " << std::endl << std::endl << logMessage << std::endl;
        return  false;
    }

    return true;
}

void ShaderProgram::setInt( std::string const& name, GLint value ){
    glUniform1i( glGetUniformLocation( id_, name.c_str() ), value );
}

}// namespace renderer  