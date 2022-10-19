#pragma once
//glad
#include "glad/glad.h"

// std
#include <string>
#include <unordered_map>

//glm
#include "glm/vec2.hpp"



namespace renderer{
    class Texture2D{
    public:// == TYPES ==
        struct Subtexture2D{
            glm::vec2 leftBottomUV{ 0.0f };
            glm::vec2 rightTopUV{ 1.0f };
        };
        using SubTexStore = std::unordered_map< std::string, Subtexture2D >;
    private:
        GLuint      id_{0};
        unsigned    width_{0};
        unsigned    height_{0};
        GLenum      mode_{};
        SubTexStore subTex_;
    public:
        Texture2D( GLuint width
            , GLuint heigh
            , unsigned char const* dataPtr
            , int nChannels = 4
            , GLenum filter= GL_LINEAR
            , GLenum wrapMode = GL_CLAMP_TO_EDGE 
        );

        Texture2D( Texture2D const& );
        Texture2D& operator =( Texture2D const& );

        ~Texture2D();

    public:
        void bind();
        void addSubtexture( std::string const& name, glm::vec2 bottomLeft, glm::vec2 topRight );
        Subtexture2D const& getSubTex( std::string const& name )const;
        unsigned width()const{
            return width_;
        }

        unsigned height()const{
            return height_;
        }
    };
}