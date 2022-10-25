#include "BrickWall.hpp"
#include "../../renderer/Sprite.hpp"

namespace game{
BrickWall::BrickWall( std::shared_ptr< renderer::Sprite > spritePtr, glm::vec2 const& pos, glm::vec2 const& sz, float angle )
: GameObject( pos, sz, angle )
, spritePtr_( spritePtr )
{}

void BrickWall::update( size_t /*deltaT*/ )
{
}

void BrickWall::render() const{
    spritePtr_->render( position_, size_, rotationAngle_ );
}

}//namespace game