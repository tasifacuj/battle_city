#pragma once

// std
#include <array>

namespace game{
    class GameStateInterface{
    public:
        virtual ~GameStateInterface() = default;
        
        virtual void render()const = 0;
        virtual void update( double deltaT ) = 0;
        virtual unsigned getStateWidth()const = 0;
        virtual unsigned getStateHeight()const = 0;
        virtual void processInput( std::array< bool, 349 > const& /*keys*/ ) {}
    };
}