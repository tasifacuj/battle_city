#include "Tank.hpp"
#include "renderer/Sprite.hpp"


namespace game{
Tank::Tank( std::shared_ptr< renderer::Sprite > spriteTop
        , std::shared_ptr< renderer::Sprite > spriteBottom
        , std::shared_ptr< renderer::Sprite > spriteLeft
        , std::shared_ptr< renderer::Sprite > spriteRight
        , float spd, glm::vec2 const& pos, glm::vec2 const& size, float layer )
: GameObject( pos, size, 0.0f, layer )
, orient_( Orienation::Top )
, spriteTop_( spriteTop )
, spriteBottom_( spriteBottom )
, spriteLeft_( spriteLeft )
, spriteRight_( spriteRight )
, isMoving_( false )
, moveOffset_( 0.0f, 1.0f )
, spd_( spd )
, animatorTop_( spriteTop_ )
, animatorBottom_( spriteBottom_ )
, animatorLeft_( spriteLeft_ )
, animatorRight_( spriteRight_ )
{
}

void Tank::update( size_t deltaT ){
    if( isMoving_ ){
        position_ += deltaT * spd_ * moveOffset_ ;
        
        switch (orient_)
        {
        case Orienation::Top:
            animatorTop_.update( deltaT );
            break;
        case Orienation::Bottom:
            animatorBottom_.update( deltaT );
            break;
        case Orienation::Left:
            animatorLeft_.update( deltaT );
            break;
        case Orienation::Right:
            animatorRight_.update( deltaT );
            break;

        default:
            break;
        }
    }
}

void Tank::render()const{
    
    switch (orient_)
    {
    case Tank::Orienation::Top:
        spriteTop_->render( position_, size_, rotationAngle_, layer_ ,  animatorTop_.getCurrentFrame() );
        break;

    case Tank::Orienation::Bottom:
        spriteBottom_->render( position_, size_, rotationAngle_, layer_, animatorBottom_.getCurrentFrame() );
        break;

    case Tank::Orienation::Left:
        spriteLeft_->render( position_, size_, rotationAngle_, layer_, animatorLeft_.getCurrentFrame() );
        break;

    case Tank::Orienation::Right:
        spriteRight_->render( position_, size_, rotationAngle_, layer_, animatorRight_.getCurrentFrame() );
        break;
    
    default:
        break;
    }
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
        moveOffset_ = glm::vec2( 0.0f, 1.0f );
        break;

    case Tank::Orienation::Bottom:
        moveOffset_ = glm::vec2( 0.0f, -1.0f );
        break;

    case Tank::Orienation::Left:
        moveOffset_ = glm::vec2( -1.0f, 0.0f );
        break;

    case Tank::Orienation::Right:
        moveOffset_ = glm::vec2( 1.0f, 0.0f );
        break;
    
    default:
        break;
    }
}

}