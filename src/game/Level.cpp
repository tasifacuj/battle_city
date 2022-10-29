#include "Level.hpp"
#include "objects/GameObjectInterface.hpp"
#include "objects/BrickWall.hpp"
#include "objects/BetonWall.hpp"
#include "../resources/ResourceManager.hpp"

// std
#include <iostream>

static const unsigned TILE_SIZE = 16;

static std::shared_ptr< game::GameObjectInterface > makeGameObject( char objectType, glm::vec2 const& pos, glm::vec2 const& sz, float angle  ){
    switch ( objectType )
    {
    case '0': return std::make_shared< game::BrickWall >( game::BrickWall::WallType::RIGHT, pos, sz, angle );
    case '1': return std::make_shared< game::BrickWall >( game::BrickWall::WallType::BOTTOM, pos, sz, angle );
    case '2': return std::make_shared< game::BrickWall >( game::BrickWall::WallType::LEFT, pos, sz, angle );
    case '3': return std::make_shared< game::BrickWall >( game::BrickWall::WallType::TOP, pos, sz, angle );
    case '4': return std::make_shared< game::BrickWall >( game::BrickWall::WallType::ALL, pos, sz, angle );
    case 'G': return std::make_shared< game::BrickWall >( game::BrickWall::WallType::BOTTOM_LEFT, pos, sz, angle );
    case 'H': return std::make_shared< game::BrickWall >( game::BrickWall::WallType::BOTTOM_RIGHT, pos, sz, angle );
    case 'I': return std::make_shared< game::BrickWall >( game::BrickWall::WallType::TOP_LEFT, pos, sz, angle );
    case 'J': return std::make_shared< game::BrickWall >( game::BrickWall::WallType::TOP_RIGHT, pos, sz, angle );

    case '5': return std::make_shared< game::BetonWall >( game::BetonWall::WallType::RIGHT, pos, sz, angle );
    case '6': return std::make_shared< game::BetonWall >( game::BetonWall::WallType::BOTTOM, pos, sz, angle );
    case '7': return std::make_shared< game::BetonWall >( game::BetonWall::WallType::LEFT, pos, sz, angle );
    case '8': return std::make_shared< game::BetonWall >( game::BetonWall::WallType::TOP, pos, sz, angle );
    case '9': return std::make_shared< game::BetonWall >( game::BetonWall::WallType::ALL, pos, sz, angle );
    default:
        std::cout << "Unknown map object " << objectType << std::endl;
        return {};
    }
}

namespace game{

Level::Level( std::vector< std::string > const& levelDescr ){
    if( levelDescr.empty() ){
        std::cout << "Empty level\n";
        return;
    }

    width_ = levelDescr[0].size();
    height_ = levelDescr.size();
    mapObjects_.reserve( width_ * height_ );
    unsigned bottomOffset = TILE_SIZE * ( height_ - 1 );

    for( auto const& row : levelDescr ){
        unsigned leftOffset = 0;

        for( char elem : row ){
            mapObjects_.emplace_back( makeGameObject( elem, glm::vec2( leftOffset, bottomOffset ), glm::vec2( TILE_SIZE, TILE_SIZE ), 0.0f ) );
            leftOffset += TILE_SIZE;
        }

        bottomOffset -= TILE_SIZE;
    }

}

void Level::update( size_t deltaT ){
    for( auto optr : mapObjects_ ){
        if( optr ){
            optr->update( deltaT );
        }
    }
}

void Level::render(){
    for( auto optr : mapObjects_ ){
        if( optr ){
            optr->render();
        }
    }
}

}// namespace game