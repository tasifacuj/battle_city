#include "Border.hpp"
#include "../../renderer/Sprite.hpp"
#include "../../resources/ResourceManager.hpp"

namespace game{

Border::Border( glm::vec2 const& pos, glm::vec2 const& size, float angle, float layer )
: GameObject( pos, size, angle, layer )
, sprite_( resources::ResourceManager::getInstance().getSprite( "border" ) )
{}

void Border::render()const{
    sprite_->render( position_ , size_, rotationAngle_, layer_, 0 );
}

}