#include "Tank.hpp"
#include "../../renderer/AnimatedSprite.hpp"
// #include "../renderer/Res"

namespace game{
Tank::Tank( std::shared_ptr< renderer::AnimatedSprite > sprite, float spd, glm::vec2 const& pos, glm::vec2 const& size )
: GameObject( pos, size, 0.0f )
, orient_( Orienation::Top )
, spritePtr_( sprite )
, isMoving_( false )
, moveOffset_( 0.0f, 1.0f )
, spd_( spd )
{
}

void Tank::update( size_t deltaT ){
    if( isMoving_ ){
        position_ += deltaT * spd_ * moveOffset_ ;
        spritePtr_->update( deltaT );
    }
}

void Tank::render()const{
    spritePtr_->render( position_, size_, rotationAngle_ );
}

void Tank::move( bool m ){
    isMoving_ = m;
}

void Tank::setOrient( Tank::Orienation orient ){
    if( orient_ == orient ) return;

    orient_ = orient;
    switch (orient_)
    {
    case Tank::Orienation::Top:
        spritePtr_->setState( "tankTopState" );
        moveOffset_ = glm::vec2( 0.0f, 1.0f );
        break;

    case Tank::Orienation::Bottom:
        spritePtr_->setState( "tankBottomState" );
        moveOffset_ = glm::vec2( 0.0f, -1.0f );
        break;

    case Tank::Orienation::Left:
        spritePtr_->setState( "tankLeftState" );
        moveOffset_ = glm::vec2( -1.0f, 0.0f );
        break;

    case Tank::Orienation::Right:
        spritePtr_->setState( "tankRightState" );
        moveOffset_ = glm::vec2( 1.0f, 0.0f );
        break;
    
    default:
        break;
    }
}

}