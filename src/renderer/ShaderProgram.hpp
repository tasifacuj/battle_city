#pragma once

// std
#include <string>

//glad
#include "glad/glad.h"

// glm
#include "glm/glm.hpp"

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
    public:// == uniforms ==
        void setInt( std::string const& name, GLint value );
        void setFloat( std::string const& name, GLfloat value );
        void setMatrix4( std::string const& matName, glm::mat4 const& m );
    private:
        bool createShader( std::string const& shaderText, GLenum type, GLuint& shaderId );
    };

}