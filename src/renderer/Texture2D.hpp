#pragma once
//glad
#include "glad/glad.h"

// std
#include <string>
namespace renderer{
    class Texture2D{
        GLuint      id_{0};
        unsigned    width_{0};
        unsigned    height_{0};
        GLenum      mode_{ -1 };
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
    };
}