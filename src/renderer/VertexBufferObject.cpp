#include "VertexBufferObject.hpp"

namespace renderer{

VertexBufferObject::~VertexBufferObject(){
    glDeleteBuffers( 1, &vbo_ );
}

void VertexBufferObject::create( const void* dataPtr, size_t size ){
    glGenBuffers( 1, &vbo_ );
    glBindBuffer( GL_ARRAY_BUFFER, vbo_ );
    glBufferData( GL_ARRAY_BUFFER, size, dataPtr, GL_STATIC_DRAW );
}

void VertexBufferObject::update( const void* dataPtr, size_t size )const{
    glBindBuffer( GL_ARRAY_BUFFER, vbo_ );
    glBufferSubData( GL_ARRAY_BUFFER, 0, size, dataPtr);
}

void VertexBufferObject::bind()const{
    glBindBuffer( GL_ARRAY_BUFFER, vbo_ );
}
void VertexBufferObject :: unbind()const{
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

}//namespace renderer