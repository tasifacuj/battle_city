#pragma once

#include "glad/glad.h"

namespace renderer{
    class VertexBufferObject{
        GLuint  vbo_{0};
    public:// == CTORS ==
        VertexBufferObject() = default;
        VertexBufferObject( VertexBufferObject const& ) = delete;
        VertexBufferObject& operator =( VertexBufferObject const& ) = delete;
        ~VertexBufferObject();

    public: // == vbo ==
        void create( const void* dataPtr, size_t size );
        void update( const void* dataPtr, size_t size )const;
        void bind()const;
        void unbind()const;
    };
}