#pragma once

// std
#include <vector>
#include <string>
#include <memory>
#include <set>
// glm
#include <glm/vec2.hpp>

// project
#include "GameStateInterface.hpp"
#include "../Game.hpp"

namespace game{
    class GameObjectInterface;
    class Tank;

    class Level : public GameStateInterface{
    public: // == TYPES ==
        using TankPtr = std::shared_ptr< game::Tank >;
    private:
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
        std::shared_ptr< game::Tank >                           tankPtr_;
        std::shared_ptr< game::Tank >                           tank2Ptr_;
        std::set< TankPtr >                                     enemies_;
        Game::GameMode                                          mode_;
    public:// == CONSTANTS ==
        static constexpr unsigned TILE_SIZE = 16;
    public:// == CTOR ==
        Level( std::vector< std::string > const& levelDescr, Game::GameMode mode );
        Level( Level const& ) = delete;
        ~Level() = default;
    
    public:// == GameStateInterface ==
        virtual void update( double deltaT ) override;
        virtual void render() const override;
        virtual unsigned int getStateWidth() const override;
        virtual unsigned int getStateHeight() const override;
        virtual void processInput( std::array< bool, 349 > const& keys ) override;
    public:// == Level ==
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
        void initPhysics();
    };
}