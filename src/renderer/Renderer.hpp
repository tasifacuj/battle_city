#pragma once

namespace renderer{
    class VertexArrayObject;
    class IndexBufferObject;
    class ShaderProgram;

    class Renderer{
    public:
        static void draw( VertexArrayObject const& vao, IndexBufferObject const& indices, ShaderProgram const& program );
        static void setClearColor( float r, float g, float b, float alpha );
        static void clear();
    };
}