#include "Bullet.hpp"
#include "../../resources/ResourceManager.hpp"
#include "../../renderer/Sprite.hpp"

namespace game{

Bullet::Bullet( double velocity, glm::vec2 const& pos, glm::vec2 const& size, glm::vec2 const& exposionSize, float layer )
: GameObject( ObjectType::BULLET, pos, size, 0.0f, layer )
, spriteTop_( resources::ResourceManager::getInstance().getSprite( "bullet_Top" ) )
, spriteBottom_( resources::ResourceManager::getInstance().getSprite( "bullet_Bottom" ) )
, spriteLeft_( resources::ResourceManager::getInstance().getSprite( "bullet_Left" ) )
, spriteRight_( resources::ResourceManager::getInstance().getSprite( "bullet_Right" ) )
, maxVelocity_( velocity )
, spriteExplosion_( resources::ResourceManager::getInstance().getSprite( "explosion" ) )
, animatorExplosion_( spriteExplosion_ )
, explosionSize_( exposionSize )
, explosionOffset_( (explosionSize_ - size_) / 2.0f ){
    setVelocity( float(velocity) );
    colliders_.emplace_back( phys::AABB{ glm::vec2( 0.0f ), size_ }  );
    explosionTimer_.setCallback( [this](){
        isExploding_ = false;
        isActive_ = false;
    } );
}

void Bullet::render()const {
    if( !isActive_ )
        return;

    if( isExploding_ ){
        switch( eOrient_ ){
            case Orientation::TOP:
                spriteExplosion_->render( position_ - explosionOffset_ + glm::vec2( 0, size_.y / 2.0f ), explosionSize_, rotationAngle_, layer_, animatorExplosion_.getCurrentFrame() );
            break;
            case Orientation::BOTTOM:
                spriteExplosion_->render( position_ - explosionOffset_ - glm::vec2( 0, size_.y / 2.0f ), explosionSize_, rotationAngle_, layer_, animatorExplosion_.getCurrentFrame() );
            break;
            case Orientation::LEFT:
                spriteExplosion_->render( position_ - explosionOffset_ - glm::vec2( size_.x / 2.0f, 0.0f ), explosionSize_, rotationAngle_, layer_, animatorExplosion_.getCurrentFrame() );
            break;
            case Orientation::RIGHT:
                spriteExplosion_->render( position_ - explosionOffset_ + glm::vec2( size_.x / 2.0f, 0.0f ), explosionSize_, rotationAngle_, layer_, animatorExplosion_.getCurrentFrame() );
            break;
        }
    }else{
        switch (eOrient_){
        case Orientation::TOP:
            spriteTop_->render( position_, size_, rotationAngle_, layer_, 0 );
            break;
        case Orientation::BOTTOM:
            spriteTop_->render( position_, size_, rotationAngle_, layer_, 0 );
            break;
        case Orientation::LEFT:
            spriteLeft_->render( position_, size_, rotationAngle_, layer_, 0 );
            break;
        case Orientation::RIGHT:
            spriteRight_->render( position_, size_, rotationAngle_, layer_ , 0);
            break;
        default:
            assert( 0 && "never should be here" );
            break;
        }
    }
}

void Bullet::fire( glm::vec2 const& position, glm::vec2 const& dir ){
    position_ = position;
    direction_ = dir;

    if( direction_.x == 0.0f ) eOrient_ = direction_.y < 0.0f ? Orientation::BOTTOM : Orientation::TOP;
    else eOrient_ = direction_.x < 0.0f ? Orientation::LEFT : Orientation::RIGHT;

    isActive_ = true;
    setVelocity( maxVelocity_ );
}

void Bullet::onCollision(){
    setVelocity( 0.0f );
    isExploding_ = true;
    animatorExplosion_.reset();
    explosionTimer_.start( animatorExplosion_.getTotalDuration() );
}

void Bullet::update(double deltaT)
{
    if( isExploding_ ){
        animatorExplosion_.update( deltaT );
        explosionTimer_.update( deltaT );
    }
}

}
