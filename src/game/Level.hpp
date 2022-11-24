#pragma once

// std
#include <vector>
#include <string>
#include <memory>

// glm
#include <glm/vec2.hpp>

namespace game{
    class GameObjectInterface;

    class Level{
        size_t                                                  width_;
        size_t                                                  height_;
        std::vector< std::shared_ptr< GameObjectInterface > >   mapObjects_;
        glm::ivec2                                              playerRespawn_1_;
        glm::ivec2                                              playerRespawn_2_;
        glm::ivec2                                              enemyRespawn_1_;
        glm::ivec2                                              enemyRespawn_2_;
        glm::ivec2                                              enemyRespawn_3_;
        unsigned                                                widthPixels_{0};
        unsigned                                                heightPixels_{0};

    public:// == CONSTANTS ==
        static constexpr unsigned TILE_SIZE = 16;
    public:// == CTOR ==
        Level( std::vector< std::string > const& levelDescr );
        Level( Level const& ) = delete;
        ~Level() = default;
    
    public:// == Level ==
        void update( double deltaT );
        void render();
        size_t width()const{
            return ( width_ + 3 ) * TILE_SIZE;
        }

        size_t height()const{
            return ( height_ + 1 ) * TILE_SIZE;
        }

        glm::ivec2 const& player1Respawn()const{
            return playerRespawn_1_;
        }

        glm::ivec2 const& player2Respawn()const{
            return playerRespawn_2_;
        }

        glm::ivec2 const& enemy1Respawn()const{
            return enemyRespawn_1_;
        }

        glm::ivec2 const& enemy2Respawn()const{
            return enemyRespawn_2_;
        }

        glm::ivec2 const& enemy3Respawn()const{
            return enemyRespawn_3_;
        }

        std::vector< std::shared_ptr< GameObjectInterface > > obectsInArea( glm::vec2 const& bottomLeft, glm::vec2 const& topRight );
    };
}