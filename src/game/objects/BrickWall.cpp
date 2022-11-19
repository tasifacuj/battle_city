#include "BrickWall.hpp"
#include "../../renderer/Sprite.hpp"
#include "../../resources/ResourceManager.hpp"

namespace game{
BrickWall::BrickWall( BrickWall::WallType wallType, glm::vec2 const& pos, glm::vec2 const& sz, float angle, float layer )
: GameObject( pos, sz, angle, layer )
, currentBrickState_{ BrickState::DESTROYED, BrickState::DESTROYED, BrickState::DESTROYED, BrickState::DESTROYED }{
    resources::ResourceManager& resm = resources::ResourceManager::getInstance();
    sprites_[ static_cast<size_t>( BrickState::ALL ) ]                   = resm.getSprite( "brickWall_All" );
    sprites_[ static_cast<size_t>(BrickState::TOP_LEFT) ]                = resm.getSprite( "brickWall_TopLeft" );
    sprites_[ static_cast<size_t>(BrickState::TOP_RIGHT) ]               = resm.getSprite( "brickWall_TopRight" );
    sprites_[ static_cast<size_t>(BrickState::TOP) ]                     = resm.getSprite( "brickWall_Top" );
    sprites_[ static_cast<size_t>(BrickState::BOTTOM_LRFT) ]             = resm.getSprite( "brickWall_BottomLeft" );
    sprites_[ static_cast<size_t>(BrickState::LEFT) ]                    = resm.getSprite( "brickWall_Left" );
    sprites_[ static_cast<size_t>(BrickState::TOP_RIGHT_BOTTOM_LEFT) ]   = resm.getSprite( "brickWall_TopRight_BottomLeft" );
    sprites_[ static_cast<size_t>(BrickState::TOP_BOTTOM_LEFT) ]         = resm.getSprite( "brickWall_Top_BottomLeft" );
    sprites_[ static_cast<size_t>(BrickState::BOTTOM_RIGHT) ]            = resm.getSprite( "brickWall_BottomRight" );
    sprites_[ static_cast<size_t>(BrickState::TOP_LEFT_BOTTOM_RIGHT) ]   = resm.getSprite( "brickWall_TopLeft_BottomRight" );
    sprites_[ static_cast<size_t>(BrickState::RIGHT) ]                   = resm.getSprite( "brickWall_Right" );
    sprites_[ static_cast<size_t>(BrickState::TOP_BOTTOM_RIGHT) ]        = resm.getSprite( "brickWall_Top_BottomRight" );
    sprites_[ static_cast<size_t>(BrickState::BOTTOM) ]                  = resm.getSprite( "brickWall_Bottom" );
    sprites_[ static_cast<size_t>(BrickState::TOP_LEFT_BOTTOM) ]         = resm.getSprite( "brickWall_TopLeft_Bottom" );
    sprites_[ static_cast<size_t>(BrickState::TOP_RIGHT_BOTTOM) ]        = resm.getSprite( "brickWall_TopRight_Bottom" );

    switch (wallType)
    {
    case WallType::ALL :
        currentBrickState_.fill( BrickState::ALL );
        break;
    case WallType::TOP:
        currentBrickState_[BrickLocation::TOP_LEFT] = BrickState::ALL;
        currentBrickState_[BrickLocation::TOP_RIGHT] = BrickState::ALL;
        break;
    
    case WallType::BOTTOM:
        currentBrickState_[BrickLocation::BOTTOM_LEFT] = BrickState::ALL;
        currentBrickState_[BrickLocation::BOTTOM_RIGHT] = BrickState::ALL;
        break;
    case WallType::LEFT:
        currentBrickState_[BrickLocation::BOTTOM_LEFT] = BrickState::ALL;
        currentBrickState_[BrickLocation::TOP_LEFT] = BrickState::ALL;
        break;
    case WallType::RIGHT:
        currentBrickState_[BrickLocation::TOP_RIGHT] = BrickState::ALL;
        currentBrickState_[BrickLocation::BOTTOM_RIGHT] = BrickState::ALL;
        break;
    case WallType::TOP_LEFT:
        currentBrickState_[BrickLocation::TOP_LEFT] = BrickState::ALL;
        break;
    case WallType::TOP_RIGHT:
        currentBrickState_[BrickLocation::TOP_RIGHT] = BrickState::ALL;
        break;
    case WallType::BOTTOM_LEFT:
        currentBrickState_[BrickLocation::BOTTOM_LEFT] = BrickState::ALL;
        break;
    case WallType::BOTTOM_RIGHT:
        currentBrickState_[BrickLocation::BOTTOM_RIGHT] = BrickState::ALL;
        break;
    default:
        assert(0);
        break;
    }
}

void BrickWall::update( double /*deltaT*/ )
{
}

void BrickWall::render() const{
    // spritePtr_->render( position_, size_, rotationAngle_, 0 );
    renderBrick( BrickLocation::BOTTOM_LEFT );
    renderBrick( BrickLocation::BOTTOM_RIGHT );
    renderBrick( BrickLocation::TOP_LEFT );
    renderBrick( BrickLocation::TOP_RIGHT );
}

void BrickWall::renderBrick( BrickWall::BrickLocation loc )const{
    static std::array< glm::vec2, 4 > offsets{
        glm::vec2( 0.0f, size_.y * 0.5f ), // top left
        glm::vec2( size_.x * 0.5f, size_.y * 0.5f ), // top right
        glm::vec2( 0.0f, 0.0f ), // bottom left
        glm::vec2( size_.x * 0.5f, 0.0f ), // bottom right
    };
    BrickState state = currentBrickState_[ loc ];

    if( state != BrickState::DESTROYED ){
        sprites_[ static_cast<size_t>(state) ]->render( position_ + offsets[ loc ], size_ * 0.5f, rotationAngle_, layer_, 0 );
    }
}

}//namespace game