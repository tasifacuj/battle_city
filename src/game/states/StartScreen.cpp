#include "StartScreen.hpp"
#include "resources/ResourceManager.hpp"
#include "renderer/Sprite.hpp"

// std
#include <stdexcept>

namespace{
std::shared_ptr< renderer::Sprite > makeDescriptionSprite( char d ){
    switch ( d )
    {
    case '0': return resources::ResourceManager::getInstance().getSprite( "brickWall_All" );
    case '1': return resources::ResourceManager::getInstance().getSprite( "brickWall_TopLeft" );
    case '2': return resources::ResourceManager::getInstance().getSprite( "brickWall_TopRight" );
    case '3': return resources::ResourceManager::getInstance().getSprite( "brickWall_Top" );
    case '4': return resources::ResourceManager::getInstance().getSprite( "brickWall_BottomLeft" );
    case '5': return resources::ResourceManager::getInstance().getSprite( "brickWall_Left" );
    case '6': return resources::ResourceManager::getInstance().getSprite( "brickWall_TopRight_BottomLeft" );
    case '7': return resources::ResourceManager::getInstance().getSprite( "brickWall_Top_BottomLeft" );
    case '8': return resources::ResourceManager::getInstance().getSprite( "brickWall_BottomRight" );
    case '9': return resources::ResourceManager::getInstance().getSprite( "brickWall_TopLeft_BottomRight" );
    case 'A': return resources::ResourceManager::getInstance().getSprite( "brickWall_Right" );
    case 'B': return resources::ResourceManager::getInstance().getSprite( "brickWall_Top_BottomRight" );
    case 'C': return resources::ResourceManager::getInstance().getSprite( "brickWall_Bottom" );
    case 'D': return resources::ResourceManager::getInstance().getSprite( "brickWall_TopLeft_Bottom" );
    case 'E': return resources::ResourceManager::getInstance().getSprite( "brickWall_TopRight_Bottom" );
    case 'F': return {};
    default:
        assert( 0 );
        return {};
    }
}
}

namespace game{

StartScreen::StartScreen( std::vector< std::string > const& description ){
    if( description.empty() ){
        throw std::runtime_error( "empty start screen" );
    }

    auto leftOffset = 2 * BLOCK_SIZE;
    auto bottomOffset = START_SCREEN_HEIGHT - 2 * BLOCK_SIZE;
    unsigned currentBottomOffset = bottomOffset;

    for( auto const& row : description ){
        unsigned currentLeftOffset = leftOffset;
        for( char e : row ){
            sprites_.emplace_back( makeDescriptionSprite( e ), glm::vec2( currentLeftOffset, currentBottomOffset ) );
            currentLeftOffset += BLOCK_SIZE;
        }

        currentBottomOffset -= BLOCK_SIZE;
    }
}

unsigned StartScreen::getStateWidth()const{
    return START_SCREEN_WIDTH;
}

unsigned StartScreen::getStateHeight()const{
    return START_SCREEN_HEIGHT;
}

void StartScreen::render()const{
    for( auto const& elems : sprites_ ){
        if( elems.first ){
            elems.first->render( elems.second, glm::vec2( BLOCK_SIZE ), 0.0f, 0.0f, 0 );
        }
    }
}

void StartScreen::update( double /*deltaT*/ )
{}

}