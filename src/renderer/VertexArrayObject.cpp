#include "VertexArrayObject.hpp"
#include "VertexBufferObject.hpp"
#include "VertexBufferLayout.hpp"

// glad
#include "glad/glad.h"

namespace renderer{
VertexArrayObject::VertexArrayObject(){
    glGenVertexArrays( 1, &vao_ );
}

VertexArrayObject::~VertexArrayObject(){
    glDeleteVertexArrays( 1, &vao_ );
}

void VertexArrayObject::bind()const{
    glBindVertexArray( vao_ );
}

void VertexArrayObject::unbind()const{
    glBindVertexArray( 0 );
}

void VertexArrayObject::addBuffer( VertexBufferObject const& vbo,  VertexBufferLayout const& layout ){
    bind();
    vbo.bind();
    auto const& elems  = layout.elements();
    GLbyte* offset = nullptr;
    
    for( size_t i = 0; i < elems.size(); i++ ){
        GLuint attribIdx = buffersCount_ + static_cast<GLuint>(i);
        glEnableVertexAttribArray( attribIdx );
        auto const& elem = elems[i];
        glVertexAttribPointer( attribIdx, elem.count, elem.type, elem.normalized, static_cast<GLsizei>(layout.stride()), offset );
        offset += elem.size;
    }

    buffersCount_ += static_cast<GLuint>( elems.size() );
}

}