#include "AnimatedSprite.hpp"
#include "Texture2D.hpp"
#include "ShaderProgram.hpp"


//std
#include <iostream>

namespace renderer{

AnimatedSprite::AnimatedSprite( std::shared_ptr< Texture2D > texPtr
    , std::string const& initialSubTexName
    , std::shared_ptr< ShaderProgram > programPtr
    , glm::vec2 const& pos 
    , glm::vec2 const& size
    , float angle
) : Sprite( texPtr, initialSubTexName, programPtr, pos, size, angle ){
    animationDurationIt_ = stateMap_.end();
}

void AnimatedSprite::setState( std::string const& newState ){
    auto it = stateMap_.find( newState );

    if( it == stateMap_.end() ){
        std::cout << "Can't find animation state " << newState << std::endl;
        return;
    }

    if( animationDurationIt_ != it ){
        animationTimeMS_ = 0;
        frame_ = 0;
        animationDurationIt_ = it;
        dirty_ = true;
    }
}

void AnimatedSprite::update( size_t deltaTMS ){
    if( animationDurationIt_ != stateMap_.end() ){
        animationTimeMS_ += deltaTMS;

        while( animationTimeMS_ >= animationDurationIt_->second.at( frame_ ).second ){
            animationTimeMS_ -= animationDurationIt_->second[  frame_ ].second;
            frame_++;
            dirty_ = true;

            if( frame_ == animationDurationIt_->second.size() ) frame_ = 0;
        }   
    }
}

void AnimatedSprite::render(){
    if( dirty_ ){
        auto const& subTex = texPtr_->getSubTex( animationDurationIt_->second[frame_].first );
        const GLfloat texCoords[] = {
            /**
             u -> v
            */

            subTex.leftBottomUV.x, subTex.leftBottomUV.y,
            subTex.leftBottomUV.x, subTex.rightTopUV.y,
            subTex.rightTopUV.x, subTex.rightTopUV.y,
            subTex.rightTopUV.x, subTex.leftBottomUV.y
        };

        texBuffer_.update( texCoords, sizeof( texCoords ) );
        dirty_ = false;
    }

    Sprite::render();
}

}//namespace renderer