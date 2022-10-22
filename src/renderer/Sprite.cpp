#include "Sprite.hpp"
#include "Texture2D.hpp"
#include "ShaderProgram.hpp"
#include "VertexBufferLayout.hpp"
#include "Renderer.hpp"

// std
#include <iostream>

// glm
#include "glm/gtc/matrix_transform.hpp"

namespace renderer{

Sprite::Sprite( std::shared_ptr< Texture2D > texPtr
            , std::string const& initialSubTexName
            , std::shared_ptr< ShaderProgram > programPtr
            , glm::vec2 const& pos
            , glm::vec2 const& size
            , float angle )
: texPtr_( texPtr )
, programPtr_( programPtr )
, position_( pos )
, size_( size )
, angle_( angle ){
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

void Sprite::render(){
    programPtr_->use();
    glm::mat4 model( 1.0f );

    // 3. translate
    model = glm::translate( model, glm::vec3( position_, 0.0f ) );
    // 2. rotate
    // 2.3 put the model back where it was
    model = glm::translate( model, glm::vec3( 0.5f * size_.x, 0.5f * size_.y, 0.0f ) );
    // 2.2 rotate
    model = glm::rotate( model, glm::radians( angle_ ), glm::vec3( 0.0f, 0.0f, 1.0f ) );
    // 2.1 put model in the world origin, because first verice is (0,0)
    model = glm::translate( model, glm::vec3( -0.5f * size_.x, -0.5f * size_.y, 0.0f ) );
    // 1. scale
    model = glm::scale( model, glm::vec3( size_, 1.0f ) );

    programPtr_->setMatrix4( "model", model );
    glActiveTexture( GL_TEXTURE0 );
    texPtr_->bind();
    // glDrawArrays( GL_TRIANGLES, 0, 6 );
    // glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr );
    Renderer::draw( vao_, indicesBuffer_, *programPtr_ );
}

}// namespace renderer
