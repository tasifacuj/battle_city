#include "Water.hpp"
#include "../../renderer/Sprite.hpp"
#include "../../resources/ResourceManager.hpp"

namespace game{

Water::Water( glm::vec2 const& pos, glm::vec2 const& size, float angle, float layer )
: GameObject( pos, size, angle, layer )
, sprite_( resources::ResourceManager::getInstance().getSprite( "water" ) )
, animator_( sprite_ )
{}

void Water::renderBlock( Location loc )const{
    static std::array< glm::vec2, 4 > offsets{
        glm::vec2( 0.0f, size_.y * 0.5f ), // top left
        glm::vec2( size_.x * 0.5f, size_.y * 0.5f ), // top right
        glm::vec2( 0.0f, 0.0f ), // bottom left
        glm::vec2( size_.x * 0.5f, 0.0f ), // bottom right
    };

    sprite_->render( position_ + offsets[ static_cast<size_t>( loc ) ], size_ * 0.5f, rotationAngle_, layer_, animator_.getCurrentFrame() );
}

void Water::update( double deltaT ){
    animator_.update( deltaT );
}

void Water::render()const{
    renderBlock( Location::TOP_LEFT );
    renderBlock( Location::TOP_RIGHT );
    renderBlock( Location::BOTTOM_LEFT );
    renderBlock( Location::BOTTOM_RIGHT );
}

}