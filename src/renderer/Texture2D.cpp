#include "Texture2D.hpp"

namespace renderer{

Texture2D::Texture2D( GLuint width
    , GLuint heigh
    , unsigned char const* dataPtr
    , int nChannels
    , GLenum filter
    , GLenum wrapMode
)
: width_( width )
, height_( heigh ){
    switch (nChannels)
    {
    case 4:
        mode_ = GL_RGBA;
        break;
    case 3:
        mode_ = GL_RGB;
        break;
    default:
        mode_ = GL_RGBA;
        break;
    }

    glGenTextures( 1, &id_ );
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, id_ );
    glTexImage2D( GL_TEXTURE_2D, 0, mode_, width_, height_, 0, mode_, GL_UNSIGNED_BYTE, dataPtr );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter );
    glGenerateMipmap( GL_TEXTURE_2D );

    glBindTexture( GL_TEXTURE_2D, 0 );
}

Texture2D::~Texture2D(){
    glDeleteTextures( 1, &id_ );
}

void Texture2D::bind(){
    glBindTexture( GL_TEXTURE_2D, id_ );
}

}// namespace renderer