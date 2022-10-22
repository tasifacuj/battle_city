#pragma once

// std
#include <vector>

//glad
#include "glad/glad.h"

namespace renderer{
    //                      ?, count, type, normalzed
    // glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, nullptr );
    class VertexBufferLayout{
    public:// == TYPES ==
        struct VertexBufferLayoutElement{
            GLuint count;
            GLenum type;
            GLboolean normalized;
            unsigned size;
        };

    private:
        std::vector< VertexBufferLayoutElement >    elems_;
        size_t                                      stride_{0};
    public:// == CTORS ==
        VertexBufferLayout() = default;

    public:
        void addElementLayoutFloat( unsigned count, bool normalize );
        
        void reserve( size_t count );
        
        size_t stride()const{
            return stride_;
        }

        std::vector<VertexBufferLayoutElement> const& elements()const{
            return elems_;
        }
    };
}