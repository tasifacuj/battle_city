#include "Level.hpp"
#include "objects/GameObjectInterface.hpp"
#include "objects/BrickWall.hpp"
#include "objects/BetonWall.hpp"
#include "../resources/ResourceManager.hpp"
#include "objects/Trees.hpp"
#include "objects/Ice.hpp"
#include "objects/Water.hpp"
#include "objects/Eagle.hpp"

// std
#include <iostream>

static const unsigned TILE_SIZE = 16;

static std::shared_ptr< game::GameObjectInterface > makeGameObject( char objectType, glm::vec2 const& pos, glm::vec2 const& sz, float angle  ){
    switch ( objectType )
    {
    case '0': return std::make_shared< game::BrickWall >( game::BrickWall::WallType::RIGHT, pos, sz, angle, 0.0f );
    case '1': return std::make_shared< game::BrickWall >( game::BrickWall::WallType::BOTTOM, pos, sz, angle, 0.0f );
    case '2': return std::make_shared< game::BrickWall >( game::BrickWall::WallType::LEFT, pos, sz, angle, 0.0f );
    case '3': return std::make_shared< game::BrickWall >( game::BrickWall::WallType::TOP, pos, sz, angle, 0.0f );
    case '4': return std::make_shared< game::BrickWall >( game::BrickWall::WallType::ALL, pos, sz, angle, 0.0f );
    case '5': return std::make_shared< game::BetonWall >( game::BetonWall::WallType::RIGHT, pos, sz, angle, 0.0f );
    case '6': return std::make_shared< game::BetonWall >( game::BetonWall::WallType::BOTTOM, pos, sz, angle, 0.0f );
    case '7': return std::make_shared< game::BetonWall >( game::BetonWall::WallType::LEFT, pos, sz, angle, 0.0f );
    case '8': return std::make_shared< game::BetonWall >( game::BetonWall::WallType::TOP, pos, sz, angle, 0.0f );
    case '9': return std::make_shared< game::BetonWall >( game::BetonWall::WallType::ALL, pos, sz, angle, 0.0f );

    case 'A': return std::make_shared< game::Water >( pos, sz, angle, 0.0f );
    case 'B': return std::make_shared< game::Trees >( pos, sz, angle, 1.0f );
    case 'C': return std::make_shared< game::Ice >( pos, sz, angle, -1.0f );
    case 'E': return std::make_shared< game::Eagle >( pos, sz, angle, 0.0f );

    case 'G': return std::make_shared< game::BrickWall >( game::BrickWall::WallType::BOTTOM_LEFT, pos, sz, angle, 0 );
    case 'H': return std::make_shared< game::BrickWall >( game::BrickWall::WallType::BOTTOM_RIGHT, pos, sz, angle, 0 );
    case 'I': return std::make_shared< game::BrickWall >( game::BrickWall::WallType::TOP_LEFT, pos, sz, angle, 0 );
    case 'J': return std::make_shared< game::BrickWall >( game::BrickWall::WallType::TOP_RIGHT, pos, sz, angle, 0 );
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