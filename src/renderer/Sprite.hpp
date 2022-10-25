#pragma once

//glad
#include "glad/glad.h"

// std
#include <memory>
#include <string>

// glm
#include "glm/vec2.hpp"

#include "VertexBufferObject.hpp"
#include "IndexBufferObject.hpp"
#include "VertexArrayObject.hpp"

namespace renderer{
    class Texture2D;
    class ShaderProgram;

    class Sprite{
    protected:// == MEMBERS ==
        std::shared_ptr< Texture2D >    texPtr_;
        std::shared_ptr< ShaderProgram >programPtr_;
        VertexArrayObject               vao_;
        VertexBufferObject              vertexBuffer_;
        VertexBufferObject              texBuffer_;
        IndexBufferObject               indicesBuffer_;
    public:// == CTOR ==
        Sprite( std::shared_ptr< Texture2D > texPtr
            , std::string const& initialSubTexName
            , std::shared_ptr< ShaderProgram > programPtr
        );

        Sprite( Sprite const& ) = delete;
        Sprite& operator =( Sprite const& ) = delete;

        virtual ~Sprite();
    
    public:// == METHODS ==
        virtual void render( glm::vec2 const& pos, glm::vec2 const& sz, float angle );
    };
}// namespace renderer