#include "IndexBufferObject.hpp"

namespace renderer{

IndexBufferObject::~IndexBufferObject(){
    glDeleteBuffers( 1, &vbo_ );
}

void IndexBufferObject::create( const void* dataPtr, size_t size ){
    glGenBuffers( 1, &vbo_ );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vbo_ );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, size, dataPtr, GL_STATIC_DRAW );
}

void IndexBufferObject::bind()const{
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vbo_ );
}
void IndexBufferObject :: unbind()const{
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

}//namespace renderer