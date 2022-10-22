#pragma once

#include "glad/glad.h"

namespace renderer{
    class IndexBufferObject{
        GLuint  vbo_{0};
    public:// == CTORS ==   
        IndexBufferObject() = default;
        IndexBufferObject( IndexBufferObject const& ) = delete;
        IndexBufferObject& operator =( IndexBufferObject const& ) = delete;
        ~IndexBufferObject();

    public: // == vbo ==
        void create( const void* dataPtr, size_t size );
        void bind()const;
        void unbind()const;
    };
}