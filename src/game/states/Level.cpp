#include "Level.hpp"
#include "game/objects/GameObjectInterface.hpp"
#include "game/objects/BrickWall.hpp"
#include "game/objects/BetonWall.hpp"
#include "resources/ResourceManager.hpp"
#include "game/objects/Trees.hpp"
#include "game/objects/Ice.hpp"
#include "game/objects/Water.hpp"
#include "game/objects/Eagle.hpp"
#include "game/objects/Border.hpp"
#include "game/objects/Tank.hpp"

// std
#include <iostream>
#include <algorithm>
#include <cmath>

//glfw
#include "GLFW/glfw3.h"

static std::shared_ptr< game::GameObjectInterface > makeGameObject( char objectType, glm::vec2 const& pos, glm::vec2 const& sz, float angle  ){
    switch ( objectType )
    {
    case '0': return std::make_shared< game::BrickWall >( game::BrickWall::EBrickWallType::Right, pos, sz, angle, 0.0f );
    case '1': return std::make_shared< game::BrickWall >( game::BrickWall::EBrickWallType::Bottom, pos, sz, angle, 0.0f );
    case '2': return std::make_shared< game::BrickWall >( game::BrickWall::EBrickWallType::Left, pos, sz, angle, 0.0f );
    case '3': return std::make_shared< game::BrickWall >( game::BrickWall::EBrickWallType::Top, pos, sz, angle, 0.0f );
    case '4': return std::make_shared< game::BrickWall >( game::BrickWall::EBrickWallType::All, pos, sz, angle, 0.0f );
    case '5': return std::make_shared< game::BetonWall >( game::BetonWall::WallType::RIGHT, pos, sz, angle, 0.0f );
    case '6': return std::make_shared< game::BetonWall >( game::BetonWall::WallType::BOTTOM, pos, sz, angle, 0.0f );
    case '7': return std::make_shared< game::BetonWall >( game::BetonWall::WallType::LEFT, pos, sz, angle, 0.0f );
    case '8': return std::make_shared< game::BetonWall >( game::BetonWall::WallType::TOP, pos, sz, angle, 0.0f );
    case '9': return std::make_shared< game::BetonWall >( game::BetonWall::WallType::ALL, pos, sz, angle, 0.0f );

    case 'A': return std::make_shared< game::Water >( pos, sz, angle, 0.0f );
    case 'B': return std::make_shared< game::Trees >( pos, sz, angle, 1.0f );
    case 'C': return std::make_shared< game::Ice >( pos, sz, angle, -1.0f );
    case 'E': return std::make_shared< game::Eagle >( pos, sz, angle, 0.0f );

    case 'G': return std::make_shared< game::BrickWall >( game::BrickWall::EBrickWallType::BottomLeft, pos, sz, angle, 0 );
    case 'H': return std::make_shared< game::BrickWall >( game::BrickWall::EBrickWallType::BottomRight, pos, sz, angle, 0 );
    case 'I': return std::make_shared< game::BrickWall >( game::BrickWall::EBrickWallType::TopLeft, pos, sz, angle, 0 );
    case 'J': return std::make_shared< game::BrickWall >( game::BrickWall::EBrickWallType::TopRight, pos, sz, angle, 0 );
    default:
        std::cout << "Unknown map object " << objectType << std::endl;
        return {};
    }
}

namespace game{

Level::Level( std::vector< std::string > const& levelDescr, Game::GameMode mode )
: mode_( mode ) {
    if( levelDescr.empty() ){
        std::cout << "Empty level\n";
        return;
    }

    width_ = levelDescr[0].size();
    height_ = levelDescr.size();
    widthPixels_ = static_cast<unsigned>( width_ * TILE_SIZE );
    heightPixels_ = static_cast<unsigned>(height_ * TILE_SIZE);
    mapObjects_.reserve( width_ * height_ + 4 );
    unsigned bottomOffset = static_cast<unsigned>(TILE_SIZE * ( height_ - 1 )// left bootom of the highest row
     + TILE_SIZE * 0.5f);// bottom panel
    playerRespawn_1_ = { TILE_SIZE * ( 0.5f * width_ - 1 ), TILE_SIZE * 0.5 };
    playerRespawn_2_ = { TILE_SIZE * ( 0.5f * width_ + 3 ), TILE_SIZE * 0.5 };
    
    enemyRespawn_1_ = { TILE_SIZE,                          TILE_SIZE  * height_ - TILE_SIZE * 0.5f };
    enemyRespawn_2_ = { TILE_SIZE * ( 0.5f * width_ - 1 ) , TILE_SIZE  * height_ - TILE_SIZE * 0.5f };
    enemyRespawn_3_ = { TILE_SIZE * width_,                 TILE_SIZE  * height_ - TILE_SIZE * 0.5f };

    for( auto const& row : levelDescr ){
        unsigned leftOffset = TILE_SIZE;

        for( char elem : row ){
            switch ( elem ){
            case 'K':
                playerRespawn_1_ = glm::ivec2( leftOffset, bottomOffset );
                mapObjects_.emplace_back( nullptr );
                break;
            case 'L':
                playerRespawn_2_ = glm::ivec2( leftOffset, bottomOffset );
                mapObjects_.emplace_back( nullptr );
                break;
            case 'M':
                enemyRespawn_1_ = glm::ivec2( leftOffset, bottomOffset );
                mapObjects_.emplace_back( nullptr );
                break;
            case 'N':
                enemyRespawn_2_ = glm::ivec2( leftOffset, bottomOffset );
                mapObjects_.emplace_back( nullptr );
                break;
            case 'O':
                enemyRespawn_3_ = glm::ivec2( leftOffset, bottomOffset );
                mapObjects_.emplace_back( nullptr );
                break;
            default:
                mapObjects_.emplace_back( makeGameObject( elem, glm::vec2( leftOffset, bottomOffset ), glm::vec2( TILE_SIZE, TILE_SIZE ), 0.0f ) );
                break;
            }
            
            leftOffset += TILE_SIZE;
        }

        bottomOffset -= TILE_SIZE;
    }

    // bottom
    mapObjects_.emplace_back( std::make_shared< game::Border >( glm::vec2( TILE_SIZE, 0 ), glm::vec2( width_ * TILE_SIZE, 0.5f * TILE_SIZE ), 0.0f, 0.0f ) );
    // top
    mapObjects_.emplace_back( std::make_shared< game::Border >( glm::vec2( TILE_SIZE, TILE_SIZE * height_ + 0.5f * TILE_SIZE ), glm::vec2( width_ * TILE_SIZE, 0.5f * TILE_SIZE ), 0.0f, 0.0f ) );
    // left
    mapObjects_.emplace_back( std::make_shared< game::Border >( glm::vec2( 0.0f, 0.0f ), glm::vec2( TILE_SIZE, TILE_SIZE * ( height_ + 1 ) ), 0.0f, 0.0f ) );
    // right
    mapObjects_.emplace_back( std::make_shared< game::Border >( glm::vec2( ( width_ + 1 ) * TILE_SIZE, 0.0f ), glm::vec2( 2 * TILE_SIZE, TILE_SIZE * ( height_ + 1 ) ), 0.0f, 0.0f ) );
    std::cout << "Map objects " << mapObjects_.size() << std::endl;
}



void Level::processInput( std::array< bool, 349 > const& keys ){
    switch ( mode_ )
    {
    case Game::GameMode::TWO_PLAYERS:
        if( keys[ GLFW_KEY_UP ] ){
            tank2Ptr_->setOrient( game::Tank::Orienation::Top );
            tank2Ptr_->setVelocity( tank2Ptr_->getMaxAllowedSpd() );
        }else if( keys[ GLFW_KEY_LEFT ] ){
            tank2Ptr_->setOrient( game::Tank::Orienation::Left );
            tank2Ptr_->setVelocity( tank2Ptr_->getMaxAllowedSpd() );
        }else if( keys[ GLFW_KEY_DOWN ] ){
            tank2Ptr_->setOrient( game::Tank::Orienation::Bottom );
            tank2Ptr_->setVelocity( tank2Ptr_->getMaxAllowedSpd() );
        }else if( keys[ GLFW_KEY_RIGHT ] ){
            tank2Ptr_->setOrient( game::Tank::Orienation::Right );
            tank2Ptr_->setVelocity( tank2Ptr_->getMaxAllowedSpd() );
        }else{
            tank2Ptr_->setVelocity( 0.0f );
        }

        if( keys[GLFW_KEY_RIGHT_SHIFT  ] ) tank2Ptr_->fire();
    
    case Game::GameMode::SINGLE_PLAYER:
        if( keys[ GLFW_KEY_W ] ){
            tankPtr_->setOrient( game::Tank::Orienation::Top );
            tankPtr_->setVelocity( tankPtr_->getMaxAllowedSpd() );
        }else if( keys[ GLFW_KEY_A ] ){
            tankPtr_->setOrient( game::Tank::Orienation::Left );
            tankPtr_->setVelocity( tankPtr_->getMaxAllowedSpd() );
        }else if( keys[ GLFW_KEY_S ] ){
            tankPtr_->setOrient( game::Tank::Orienation::Bottom );
            tankPtr_->setVelocity( tankPtr_->getMaxAllowedSpd() );
        }else if( keys[ GLFW_KEY_D ] ){
            tankPtr_->setOrient( game::Tank::Orienation::Right );
            tankPtr_->setVelocity( tankPtr_->getMaxAllowedSpd() );
        }else{
            tankPtr_->setVelocity( 0.0f );
        }

        if( keys[GLFW_KEY_SPACE  ] ) tankPtr_->fire();
    default:
        break;
    }

    if( keys[ GLFW_KEY_W ] ){
        tankPtr_->setOrient( game::Tank::Orienation::Top );
        tankPtr_->setVelocity( tankPtr_->getMaxAllowedSpd() );
    }else if( keys[ GLFW_KEY_A ] ){
        tankPtr_->setOrient( game::Tank::Orienation::Left );
        tankPtr_->setVelocity( tankPtr_->getMaxAllowedSpd() );
    }else if( keys[ GLFW_KEY_S ] ){
        tankPtr_->setOrient( game::Tank::Orienation::Bottom );
        tankPtr_->setVelocity( tankPtr_->getMaxAllowedSpd() );
    }else if( keys[ GLFW_KEY_D ] ){
        tankPtr_->setOrient( game::Tank::Orienation::Right );
        tankPtr_->setVelocity( tankPtr_->getMaxAllowedSpd() );
    }else{
        tankPtr_->setVelocity( 0.0f );
    }

    if( keys[GLFW_KEY_SPACE  ] ) tankPtr_->fire();
}

void Level::initPhysics(){
    auto& resm = resources::ResourceManager::getInstance();
    auto& ph = phys::PhysicsEngine::getInstance();

    switch (mode_){
    case Game::GameMode::TWO_PLAYERS:
        tank2Ptr_ = std::make_shared< game::Tank >( 
            Tank::ETankType::Player1Yellow_type1
            , false
            , true
            , game::Tank::Orienation::Top
            , 0.05f
            , player2Respawn()
            , glm::vec2( game::Level::TILE_SIZE, game::Level::TILE_SIZE )
            , 0.0f 
        );
        ph.add( tank2Ptr_ );
    case Game::GameMode::SINGLE_PLAYER:
        tankPtr_ = std::make_shared< game::Tank >( 
            Tank::ETankType::Player2Green_type2
            , false
            , true
            , game::Tank::Orienation::Top
            , 0.05f
            , player1Respawn()
            , glm::vec2( game::Level::TILE_SIZE, game::Level::TILE_SIZE )
            , 0.0f 
        );
        ph.add( tankPtr_ );
    default:
        break;
    }

    enemies_.emplace( std::make_shared< game::Tank >( Tank::ETankType::EnemyRed_type1, true, false, game::Tank::Orienation::Bottom, 0.05f, enemy1Respawn(), glm::vec2( game::Level::TILE_SIZE, game::Level::TILE_SIZE ), 0.0f ) );
    enemies_.emplace( std::make_shared< game::Tank >( Tank::ETankType::EnemyRed_type2, true, false, game::Tank::Orienation::Bottom, 0.05f, enemy2Respawn(), glm::vec2( game::Level::TILE_SIZE, game::Level::TILE_SIZE ), 0.0f ) );
    enemies_.emplace( std::make_shared< game::Tank >( Tank::ETankType::EnemyRed_type3, true, false, game::Tank::Orienation::Bottom, 0.05f, enemy3Respawn(), glm::vec2( game::Level::TILE_SIZE, game::Level::TILE_SIZE ), 0.0f ) );

    for( auto& e: enemies_ ){
        ph.add( e );
    }
}

void Level::update( double deltaT ){
    switch (mode_){
    case Game::GameMode::TWO_PLAYERS:
        tank2Ptr_ -> update( deltaT );
    case Game::GameMode::SINGLE_PLAYER:
        tankPtr_ -> update( deltaT );
    default:
        break;
    }

    for( auto optr : mapObjects_ ){
        if( optr ){
            optr->update( deltaT );
        }
    }

    for( auto& e: enemies_ ){
        e->update( deltaT );
    }
}

void Level::render()const{
    switch (mode_){
    case Game::GameMode::TWO_PLAYERS:
        tank2Ptr_ -> render();
    case Game::GameMode::SINGLE_PLAYER:
        tankPtr_ -> render();
    default:
        break;
    }

    for( auto optr : mapObjects_ ){
        if( optr ){
            optr->render();
        }
    }

    for( auto& e: enemies_ ){
        e->render();
    }
}

std::vector< std::shared_ptr< GameObjectInterface > > Level::obectsInArea( glm::vec2 const& bottomLeft, glm::vec2 const& topRight ){
    // std::cout << "bottomLeft = {" << bottomLeft.x << "," << bottomLeft.y << "}, topRight = {" << topRight.x << "," << topRight.y << "}" << std::endl;
    glm::vec2 bottomLeftLocal( std::clamp( bottomLeft.x - TILE_SIZE, 0.0f, float(TILE_SIZE * width_) ), 
                                std::clamp( height_ * TILE_SIZE - bottomLeft.y + TILE_SIZE * 0.5f, 0.0f, float(height_ * TILE_SIZE) ) 
                            );
    glm::vec2 topRightLocal( std::clamp( topRight.x - TILE_SIZE, 0.0f, static_cast<float>(widthPixels_) ), 
                            std::clamp( height_ * TILE_SIZE - topRight.y + TILE_SIZE * 0.5f, 0.0f, static_cast<float>( heightPixels_ ) ) 
                            );
    std::vector< std::shared_ptr< GameObjectInterface > > result;
    size_t startX = static_cast<size_t>( std::floor( bottomLeftLocal.x / TILE_SIZE ) );
    size_t endX = static_cast<size_t>( std::ceil( topRightLocal.x / TILE_SIZE ) );

    size_t startY = static_cast<size_t>( std::floor( topRightLocal.y / TILE_SIZE ) );
    size_t endY = static_cast<size_t>( std::ceil( bottomLeftLocal.y / TILE_SIZE ) );

    for( size_t c = startX; c < endX; c++ ){
        for( size_t r = startY; r < endY; r++ ){
            size_t idx = r * width_ + c;
            
            try{
                auto o = mapObjects_.at( idx );
                if( o ) result.push_back( o );
            }catch( std::exception const& ex ){
                std::cout << "Level::obectsInArea: " << ex.what() << ", id = " << idx << std::endl;
            }
        }
    }

    // std::cout 
    // // << "bottomLeftLocal = {" << bottomLeftLocal.x << "," << bottomLeftLocal.y << "}, topRightLocal = {" << topRightLocal.x << "," << topRightLocal.y << "}" << std::endl
    // << "startx = " << startX << ", endX = " << endX << ", startY = " << startY << ", endY = " << endY  << ", found " << result.size()
    //  << std::endl;

    if( startX <= 1 )       result.push_back( mapObjects_[ mapObjects_.size() - 2 ] );
    if( endX >= width_ )    result.push_back( mapObjects_[ mapObjects_.size() - 1 ] );
    if( startY <= 1 )       result.push_back( mapObjects_[ mapObjects_.size() - 3 ] );
    if( endY >= height_ )   result.push_back( mapObjects_[ mapObjects_.size() - 4 ] );
    
    return result;
}

unsigned int Level::getStateWidth() const{
    return static_cast< unsigned >( width() );
}

unsigned int Level::getStateHeight() const{
    return static_cast< unsigned >( height() );
}

}// namespace game