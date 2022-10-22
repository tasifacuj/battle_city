#include "Sprite.hpp"
#include "Texture2D.hpp"
#include "ShaderProgram.hpp"

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

    glGenVertexArrays( 1, &vao_ );
    glBindVertexArray( vao_ );

        glGenBuffers( 1, &vertexVBO_ );
        glBindBuffer( GL_ARRAY_BUFFER, vertexVBO_ );
        glBufferData( GL_ARRAY_BUFFER, sizeof( vertexCoords ), vertexCoords, GL_STATIC_DRAW );

        // textures vbo
        glGenBuffers( 1, &texVBO_ );
        glBindBuffer( GL_ARRAY_BUFFER, texVBO_ );
        glBufferData( GL_ARRAY_BUFFER, sizeof( texCoords ), texCoords, GL_STATIC_DRAW );
    
        glEnableVertexAttribArray(0);
        glBindBuffer( GL_ARRAY_BUFFER, vertexVBO_ );
        glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, nullptr );

        glEnableVertexAttribArray( 1 );
        glBindBuffer( GL_ARRAY_BUFFER, texVBO_ );
        glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, nullptr );

        glGenBuffers( 1, &indicesVBO_ );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indicesVBO_ );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

Sprite::~Sprite(){
    glDeleteVertexArrays( 1, &vao_ );
    glDeleteBuffers( 1, &vertexVBO_ );
    glDeleteBuffers( 1, &indicesVBO_ );
    glDeleteBuffers( 1, &texVBO_ );
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
    glBindVertexArray( vao_ );
        glActiveTexture( GL_TEXTURE0 );
        texPtr_->bind();
        // glDrawArrays( GL_TRIANGLES, 0, 6 );
        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr );
    glBindVertexArray( 0 );
}

}// namespace renderer
