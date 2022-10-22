#pragma once

#include "glad/glad.h"

namespace renderer{
    class IndexBufferObject{
        GLuint  vbo_{0};
        GLuint count_{ 0 };
    public:// == CTORS ==   
        IndexBufferObject() = default;
        IndexBufferObject( IndexBufferObject const& ) = delete;
        IndexBufferObject& operator =( IndexBufferObject const& ) = delete;
        ~IndexBufferObject();

    public: // == vbo ==
        void create( const void* dataPtr, GLuint cnt );
        void bind()const;
        void unbind()const;
        GLuint count()const{
            return count_;
        }
    };
}