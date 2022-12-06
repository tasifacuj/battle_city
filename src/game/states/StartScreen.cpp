#include "StartScreen.hpp"
#include "resources/ResourceManager.hpp"
#include "renderer/Sprite.hpp"
#include "../Game.hpp"

// std
#include <stdexcept>

//glfw
#include "GLFW/glfw3.h"

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

StartScreen::StartScreen( std::vector< std::string > const& description, Game& game )
: menuSprite_( std::make_pair( resources::ResourceManager::getInstance().getSprite( "menu" ), glm::vec2( 11 * BLOCK_SIZE, START_SCREEN_HEIGHT - description.size() * BLOCK_SIZE - MENU_HEIGHT - 5 * BLOCK_SIZE ) ) )
, tankSprite_( std::make_pair( resources::ResourceManager::getInstance().getSprite( "player1_yellow_tank_type1_sprite_right" ), glm::vec2( 8 * BLOCK_SIZE, menuSprite_.second.y + 6 * BLOCK_SIZE - currentMenuSelection_ * BLOCK_SIZE * 2 ) ) )
, tankAnimator_( tankSprite_.first )
, game_( game ){
    if( description.empty() ){
        throw std::runtime_error( "empty start screen" );
    }

    auto leftOffset = 4 * BLOCK_SIZE;
    auto bottomOffset = START_SCREEN_HEIGHT - 4 * BLOCK_SIZE;
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

    menuSprite_.first->render( menuSprite_.second, glm::vec2( MENU_WIDTH, MENU_HEIGHT ), 0.0f, 0.0f, 0 );
    tankSprite_.first->render( glm::vec2( tankSprite_.second.x, tankSprite_.second.y - currentMenuSelection_ * TANK_SIZE ), glm::vec2( TANK_SIZE ), 0.0f, 0.0f, tankAnimator_.getCurrentFrame() );
}

void StartScreen::update( double deltaT ){
    tankAnimator_.update( deltaT );
}

void StartScreen::processInput( std::array< bool, 349 > const& keys ){
    if( !keys[ GLFW_KEY_W ] && !keys[ GLFW_KEY_S ] ) keyWasReleased_ = true;

    if( keyWasReleased_ ){
        if( keys[ GLFW_KEY_W ] ){
            keyWasReleased_ = false;
            currentMenuSelection_ --;

            if( currentMenuSelection_ < 0 ) currentMenuSelection_ = 2;
        }else if( keys[ GLFW_KEY_S ] ){
            keyWasReleased_ = false;
            currentMenuSelection_ ++;
            if( currentMenuSelection_ > 2 ) currentMenuSelection_ = 0;
        }
    }

    if( keys[ GLFW_KEY_ENTER ] ){
        switch ( currentMenuSelection_ )
        {
        case 0:
            game_.startNewLevel( 0 );
            break;
        
        default:
            break;
        }
    }
}

}