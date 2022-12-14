#include "Sprite.hpp"
#include "Texture2D.hpp"
#include "ShaderProgram.hpp"
#include "VertexBufferLayout.hpp"
#include "Renderer.hpp"

// std
#include <iostream>
#include <limits>
// glm
#include "glm/gtc/matrix_transform.hpp"

namespace renderer{

Sprite::Sprite( std::shared_ptr< Texture2D > texPtr
            , std::string const& initialSubTexName
            , std::shared_ptr< ShaderProgram > programPtr)
: texPtr_( texPtr )
, programPtr_( programPtr ){
    const GLfloat vertexCoords[] = {
        /**
         * 1--2
         * | /|
         * 0--3
        */

        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };
    auto const& subTex = texPtr_->getSubTex( initialSubTexName );
    const GLfloat texCoords[] = {
        /**
           u -> v
        */

        subTex.leftBottomUV.x, subTex.leftBottomUV.y,
        subTex.leftBottomUV.x, subTex.rightTopUV.y,
        subTex.rightTopUV.x, subTex.rightTopUV.y,
        subTex.rightTopUV.x, subTex.leftBottomUV.y
    };


    const GLuint indices[] = {
        0, 1, 2, 
        2, 3, 0
    };

    vao_.bind();
        vertexBuffer_.create( vertexCoords, sizeof( vertexCoords ) );
        VertexBufferLayout vertexLayout;
        vertexLayout.addElementLayoutFloat( 2, false );
        vao_.addBuffer( vertexBuffer_, vertexLayout );

        texBuffer_.create( texCoords, sizeof( texCoords ) );
        VertexBufferLayout textureLayout;
        textureLayout.addElementLayoutFloat( 2, false );
        vao_.addBuffer( texBuffer_, textureLayout );

        indicesBuffer_.create( indices, 6 );

    vao_.unbind();
    indicesBuffer_.unbind();
}

Sprite::~Sprite()
{
}

void Sprite::render( glm::vec2 const& pos, glm::vec2 const& sz, float angle, float layer, size_t frameId ){
    if( frameId != frameId_ ){
        auto const& fd = frames_[ frameId ];

        const GLfloat texCoords[] = {
            /**
             u -> v
            */

            fd.leftBottomUV.x, fd.leftBottomUV.y,
            fd.leftBottomUV.x, fd.rightTopUV.y,
            fd.rightTopUV.x, fd.rightTopUV.y,
            fd.rightTopUV.x, fd.leftBottomUV.y
        };

        texBuffer_.update( texCoords, sizeof( texCoords ) );
        frameId_ = frameId;
    }
    
    programPtr_->use();
    glm::mat4 model( 1.0f );

    // 3. translate
    model = glm::translate( model, glm::vec3( pos, 0.0f ) );
    // 2. rotate
    // 2.3 put the model back where it was
    model = glm::translate( model, glm::vec3( 0.5f * sz.x, 0.5f * sz.y, 0.0f ) );
    // 2.2 rotate
    model = glm::rotate( model, glm::radians( angle ), glm::vec3( 0.0f, 0.0f, 1.0f ) );
    // 2.1 put model in the world origin, because first verice is (0,0)
    model = glm::translate( model, glm::vec3( -0.5f * sz.x, -0.5f * sz.y, 0.0f ) );
    // 1. scale
    model = glm::scale( model, glm::vec3( sz, 1.0f ) );

    programPtr_->setMatrix4( "model", model );
    programPtr_->setFloat( "layer", layer );

    glActiveTexture( GL_TEXTURE0 );
    texPtr_->bind();
    // glDrawArrays( GL_TRIANGLES, 0, 6 );
    // glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr );
    Renderer::draw( vao_, indicesBuffer_, *programPtr_ );
}

}// namespace renderer
