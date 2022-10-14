#pragma once

// std
#include <string>

//glad
#include "glad/glad.h"

namespace renderer{
    class ShaderProgram{
    private:
        bool    isCompiled_{ false };
        GLuint  id_{0};
    public:
        ShaderProgram( std::string const& vertexShader, std::string const& fragShader );
        ShaderProgram( ShaderProgram const& ) = delete;
        ShaderProgram& operator =( ShaderProgram const& ) = delete;
        ~ShaderProgram();

    public:
        bool isCompiled()const{
            return isCompiled_;
        }

        void use();

    private:
        bool createShader( std::string const& shaderText, GLenum type, GLuint& shaderId );
    };

}