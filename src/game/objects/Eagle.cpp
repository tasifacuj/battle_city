#include "Eagle.hpp"
#include "../../renderer/Sprite.hpp"
#include "../../resources/ResourceManager.hpp"

namespace game{

Eagle::Eagle( glm::vec2 const& pos, glm::vec2 const& size, float angle )
: GameObject( pos, size, angle )
, sprite_( resources::ResourceManager::getInstance().getSprite( "eagle" ) )
, deadsprite_( resources::ResourceManager::getInstance().getSprite( "eagle_dead" ) )
{}

void Eagle::render()const{
    sprite_->render( position_ , size_ , rotationAngle_, 0 );
}

}