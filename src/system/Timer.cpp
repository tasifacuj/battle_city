#include "Timer.hpp"

namespace sys{

void Timer::start( double duration ){
    timeLeft_ = duration;
    active_ = true;
}

void Timer::update( double deltaT ){
    if( active_ ){
        timeLeft_ -= deltaT;

        if( timeLeft_ <= 0.0 ){
            active_ = false;
            cb_();
        }
    }
}

}