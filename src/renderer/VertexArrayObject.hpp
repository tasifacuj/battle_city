#pragma once

#include "glad/glad.h"

namespace renderer{
    class VertexBufferObject;
    class VertexBufferLayout;

    class VertexArrayObject{
        GLuint  vao_{0};
        GLuint  buffersCount_{0};
    public:// == CTORS ==
        VertexArrayObject();
        VertexArrayObject( VertexArrayObject const& ) = delete;
        VertexArrayObject& operator =( VertexArrayObject const& ) = delete;
        ~VertexArrayObject();

    public: // == vao ==
        void bind()const;
        void unbind()const;
        void addBuffer( VertexBufferObject const& vbo,  VertexBufferLayout const& layout );
    };
}