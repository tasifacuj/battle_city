#pragma once

#include <functional>

namespace sys{
    class Timer{
        std::function< void() > cb_;
        double                  timeLeft_{0.0};
        bool                    active_{false};
    public:// == Timer ==
        void update( double deltaT );
        
        void start( double duration );
        
        void setCallback( std::function< void() > cb ){
            cb_ = cb;
        }
    };
}