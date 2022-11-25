#include "SpriteAnimator.hpp"
#include "Sprite.hpp"

namespace renderer{

SpriteAnimator::SpriteAnimator( std::shared_ptr< Sprite > spritePtr )
: spritePtr_( spritePtr )
, frameDuration_( spritePtr->getFrameDuration( 0 ) ){
    for( size_t frameId = 0; frameId < spritePtr_->getFramesCount(); frameId++ ) totalDurationMS_ += spritePtr_->getFrameDuration( frameId );
}

void SpriteAnimator::update( double deltaT ){
    animationTime_ += deltaT;

    while( animationTime_ >= frameDuration_ ){
        animationTime_ -= frameDuration_;
        frame_++;

        if( frame_ == spritePtr_->getFramesCount() ) frame_ = 0;

        frameDuration_ = spritePtr_->getFrameDuration( 0 );
    }
}

void SpriteAnimator::reset(){
    frame_ = 0;
    frameDuration_ = spritePtr_->getFrameDuration( 0 );
    animationTime_ = 0;
}

}