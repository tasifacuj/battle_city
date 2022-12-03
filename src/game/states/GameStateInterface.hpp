#pragma once

namespace game{
    class GameStateInterface{
    public:
        virtual ~GameStateInterface() = default;
        
        virtual void render()const = 0;
        virtual void update( double deltaT ) = 0;
        virtual unsigned getStateWidth()const = 0;
        virtual unsigned getStateHeight()const = 0;
    };
}