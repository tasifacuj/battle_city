#include "Trees.hpp"
#include "../../renderer/Sprite.hpp"
#include "../../resources/ResourceManager.hpp"

namespace game{

Trees::Trees( glm::vec2 const& pos, glm::vec2 const& size, float angle )
: GameObject( pos, size, angle )
, sprite_( resources::ResourceManager::getInstance().getSprite( "trees" ) )
{}

void Trees::renderBlock( Location loc )const{
    static std::array< glm::vec2, 4 > offsets{
        glm::vec2( 0.0f, size_.y * 0.5f ), // top left
        glm::vec2( size_.x * 0.5f, size_.y * 0.5f ), // top right
        glm::vec2( 0.0f, 0.0f ), // bottom left
        glm::vec2( size_.x * 0.5f, 0.0f ), // bottom right
    };

    sprite_->render( position_ + offsets[ static_cast<size_t>( loc ) ], size_ * 0.5f, rotationAngle_, 0 );
}

void Trees::render()const{
    renderBlock( Location::TOP_LEFT );
    renderBlock( Location::TOP_RIGHT );
    renderBlock( Location::BOTTOM_LEFT );
    renderBlock( Location::BOTTOM_RIGHT );
}

}