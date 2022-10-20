#pragma once

//glad
#include "glad/glad.h"

// std
#include <memory>
#include <string>

// glm
#include "glm/vec2.hpp"

namespace renderer{
    class Texture2D;
    class ShaderProgram;

    class Sprite{
    protected:// == MEMBERS ==
        std::shared_ptr< Texture2D >    texPtr_;
        std::shared_ptr< ShaderProgram >programPtr_;
        glm::vec2                       position_;
        glm::vec2                       size_;
        float                           angle_;
        GLuint                          vao_{ 0 };
        GLuint                          vertexVBO_{ 0 };
        GLuint                          texVBO_{ 0 };
        
    public:// == CTOR ==
        Sprite( std::shared_ptr< Texture2D > texPtr
            , std::string const& initialSubTexName
            , std::shared_ptr< ShaderProgram > programPtr
            , glm::vec2 const& pos = glm::vec2( 0.0f )
            , glm::vec2 const& size = glm::vec2( 1.0f )
            , float angle = 0.0f );

        Sprite( Sprite const& ) = delete;
        Sprite& operator =( Sprite const& ) = delete;

        virtual ~Sprite();
    
    public:// == METHODS ==
        virtual void render();
        
        void setPosition( glm::vec2 const& p ){
            position_ = p;
        }

        void setSize( glm::vec2 const& s ){
            size_ = s;
        }

        void rotate( float angle ){
            angle_ = angle;
        }
    };
}// namespace renderer