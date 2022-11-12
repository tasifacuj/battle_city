#include "Eagle.hpp"
#include "../../renderer/Sprite.hpp"
#include "../../resources/ResourceManager.hpp"

namespace game{

Eagle::Eagle( glm::vec2 const& pos, glm::vec2 const& size, float angle, float layer )
: GameObject( pos, size, angle, layer )
, sprite_( resources::ResourceManager::getInstance().getSprite( "eagle" ) )
, deadsprite_( resources::ResourceManager::getInstance().getSprite( "eagle_dead" ) )
{}

void Eagle::render()const{
    sprite_->render( position_ , size_ , rotationAngle_, layer_, 0 );
}

}