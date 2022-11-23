#include "PhysicsEngine.hpp"
#include "../game/objects/GameObjectInterface.hpp"

namespace phys{

PhysicsEngine& PhysicsEngine::getInstance(){
    static PhysicsEngine s_inst;
    return s_inst;
}

PhysicsEngine::~PhysicsEngine(){
    terminate();
}

void PhysicsEngine::init()
{
}

void PhysicsEngine::terminate(){
    dynamicObjects_.clear();
}

void PhysicsEngine::update( double deltaT ){
    for( auto & o : dynamicObjects_ ){
        auto const& v = o->getCurrentVelocity();

        if( v > 0.0f ){
            auto const& pos = o->getCurrentPosition();
            auto const& dir = o->getCurrentDirection();
            o->setCurrentPosition( pos + dir * v * float(deltaT) );
        }
    }
}

void PhysicsEngine::add( std::shared_ptr< game::GameObjectInterface > obj ){
    dynamicObjects_.insert( obj );
}

}// namespace phys