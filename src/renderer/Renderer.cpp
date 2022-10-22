#include "Renderer.hpp"
#include "VertexArrayObject.hpp"
#include "IndexBufferObject.hpp"
#include "ShaderProgram.hpp"

namespace renderer{

void Renderer::draw( VertexArrayObject const& vao, IndexBufferObject const& indices, ShaderProgram const& /*program*/ ){
    vao.bind();
        // indices.bind();
        glActiveTexture( GL_TEXTURE0 );
        glDrawElements( GL_TRIANGLES, indices.count(), GL_UNSIGNED_INT, nullptr );
    vao.unbind();
}

void Renderer::setClearColor( float r, float g, float b, float alpha ){
    glClearColor( r, g, b, alpha );
}

void Renderer::clear(){
    glClear(GL_COLOR_BUFFER_BIT);
}

}