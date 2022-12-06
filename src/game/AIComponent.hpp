#pragma once

namespace game{
    class Tank;

    class AIComponent{
        game::Tank& tank_;
    public:// == CTOR ==
        AIComponent( game::Tank& tank );
    
    public:
        void update( double deltaT );
    };
}