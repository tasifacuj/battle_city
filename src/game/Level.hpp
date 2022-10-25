#pragma once

// std
#include <vector>
#include <string>
#include <memory>
namespace game{
    class GameObjectInterface;

    class Level{
        size_t                                                  width_;
        size_t                                                  height_;
        std::vector< std::shared_ptr< GameObjectInterface > >   mapObjects_;

    public:// == CTOR ==
        Level( std::vector< std::string > const& levelDescr );
        Level( Level const& ) = delete;
        ~Level() = default;
    
    public:// == Level ==
        void update( size_t deltaT );
        void render();
    };
}