#include "BetonWall.hpp"
#include "../../renderer/Sprite.hpp"
#include "../../resources/ResourceManager.hpp"

namespace game{
BetonWall::BetonWall( BetonWall::WallType wallType, glm::vec2 const& pos, glm::vec2 const& sz, float angle, float layer )
: GameObject( pos, sz, angle, layer )
, currentState_{ State::DESTROYED, State::DESTROYED, State::DESTROYED, State::DESTROYED }{
    resources::ResourceManager& resm = resources::ResourceManager::getInstance();
    sprite_ = resm.getSprite( "betonWall" );
    

    switch (wallType)
    {
    case WallType::ALL :
        currentState_.fill( State::ENABLED );
        break;
    case WallType::TOP:
        currentState_[Location::TOP_LEFT] = State::ENABLED;
        currentState_[Location::TOP_RIGHT] = State::ENABLED;
        break;
    
    case WallType::BOTTOM:
        currentState_[Location::BOTTOM_LEFT] = State::ENABLED;
        currentState_[Location::BOTTOM_RIGHT] = State::ENABLED;
        break;
    case WallType::LEFT:
        currentState_[Location::BOTTOM_LEFT] = State::ENABLED;
        currentState_[Location::TOP_LEFT] = State::ENABLED;
        break;
    case WallType::RIGHT:
        currentState_[Location::TOP_RIGHT] = State::ENABLED;
        currentState_[Location::BOTTOM_RIGHT] = State::ENABLED;
        break;
    case WallType::TOP_LEFT:
        currentState_[Location::TOP_LEFT] = State::ENABLED;
        break;
    case WallType::TOP_RIGHT:
        currentState_[Location::TOP_RIGHT] = State::ENABLED;
        break;
    case WallType::BOTTOM_LEFT:
        currentState_[Location::BOTTOM_LEFT] = State::ENABLED;
        break;
    case WallType::BOTTOM_RIGHT:
        currentState_[Location::BOTTOM_RIGHT] = State::ENABLED;
        break;
    default:
        assert(0);
        break;
    }
}

void BetonWall::update( size_t /*deltaT*/ )
{
}

void BetonWall::render() const{
    // spritePtr_->render( position_, size_, rotationAngle_, 0 );
    renderBrick( Location::BOTTOM_LEFT );
    renderBrick( Location::BOTTOM_RIGHT );
    renderBrick( Location::TOP_LEFT );
    renderBrick( Location::TOP_RIGHT );
}

void BetonWall::renderBrick( BetonWall::Location loc )const{
    static std::array< glm::vec2, 4 > offsets{
        glm::vec2( 0.0f, size_.y * 0.5f ), // top left
        glm::vec2( size_.x * 0.5f, size_.y * 0.5f ), // top right
        glm::vec2( 0.0f, 0.0f ), // bottom left
        glm::vec2( size_.x * 0.5f, 0.0f ), // bottom right
    };
    State state = currentState_[ loc ];

    if( state != State::DESTROYED ){
        sprite_->render( position_ + offsets[ loc ], size_ * 0.5f, rotationAngle_, layer_, 0 );
    }
}

}//namespace game