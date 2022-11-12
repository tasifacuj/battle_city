#pragma once

//glad
#include "glad/glad.h"

// std
#include <memory>
#include <string>
#include <vector>

// glm
#include "glm/vec2.hpp"

#include "VertexBufferObject.hpp"
#include "IndexBufferObject.hpp"
#include "VertexArrayObject.hpp"

namespace renderer{
    class Texture2D;
    class ShaderProgram;

    class Sprite{
    public:// == TYPES ==
        struct FrameDescription{
            glm::vec2   leftBottomUV;//!< texture coord
            glm::vec2   rightTopUV;  //!< texture coord
            size_t      duration;
        };
    protected:// == MEMBERS ==
        std::shared_ptr< Texture2D >    texPtr_;
        std::shared_ptr< ShaderProgram >programPtr_;
        VertexArrayObject               vao_;
        VertexBufferObject              vertexBuffer_;
        VertexBufferObject              texBuffer_;
        IndexBufferObject               indicesBuffer_;
        std::vector<FrameDescription>   frames_;
        size_t                          frameId_{0};
    public:// == CTOR ==
        Sprite( std::shared_ptr< Texture2D > texPtr
            , std::string const& initialSubTexName
            , std::shared_ptr< ShaderProgram > programPtr
        );

        Sprite( Sprite const& ) = delete;
        Sprite& operator =( Sprite const& ) = delete;

        virtual ~Sprite();
    
    public:// == METHODS ==
        virtual void render( glm::vec2 const& pos, glm::vec2 const& sz, float angle, float layer, size_t frameId );

        size_t getFrameDuration( size_t frameId )const{
            return frames_[ frameId ].duration;
        }

        size_t getFramesCount()const{
            return frames_.size();
        }

        void setFrames( std::vector<FrameDescription>&& frames ){
            frames_ = std::forward< std::vector<FrameDescription> >( frames );
        }
    };
}// namespace renderer