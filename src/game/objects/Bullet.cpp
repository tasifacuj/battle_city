#include "Bullet.hpp"
#include "../../resources/ResourceManager.hpp"
#include "../../renderer/Sprite.hpp"

namespace game{

Bullet::Bullet( double velocity, glm::vec2 const& pos, glm::vec2 const& size, float layer )
: GameObject( pos, size, 0.0f, layer )
, spriteTop_( resources::ResourceManager::getInstance().getSprite( "bullet_Top" ) )
, spriteBottom_( resources::ResourceManager::getInstance().getSprite( "bullet_Bottom" ) )
, spriteLeft_( resources::ResourceManager::getInstance().getSprite( "bullet_Left" ) )
, spriteRight_( resources::ResourceManager::getInstance().getSprite( "bullet_Right" ) ){
    setVelocity( float(velocity) );
    colliders_.emplace_back( phys::AABB{ glm::vec2( 0.0f ), size_ }  );
}

void Bullet::render()const {
    switch (eOrient_)
    {
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

void Bullet::fire( glm::vec2 const& position, glm::vec2 const& dir ){
    position_ = position;
    direction_ = dir;

    if( direction_.x == 0.0f ) eOrient_ = direction_.y < 0.0f ? Orientation::BOTTOM : Orientation::TOP;
    else eOrient_ = direction_.x < 0.0f ? Orientation::LEFT : Orientation::RIGHT;

    isActive_ = true;
}

}
