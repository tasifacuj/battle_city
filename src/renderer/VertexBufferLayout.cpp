#include "VertexBufferLayout.hpp"

namespace renderer{

void VertexBufferLayout::reserve( size_t count ){
    elems_.reserve( count );
}

void VertexBufferLayout::addElementLayoutFloat( unsigned count, bool normalized ){
    elems_.push_back( { count, GL_FLOAT, normalized } );
    stride_ += elems_.back().size;
}

}//namespace renderer