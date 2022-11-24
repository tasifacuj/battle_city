#include "PhysicsEngine.hpp"
#include "../game/objects/GameObjectInterface.hpp"
#include "../game/Level.hpp"

namespace phys{

PhysicsEngine& PhysicsEngine::getInstance(){
    static PhysicsEngine s_inst;
    return s_inst;
}

PhysicsEngine::~PhysicsEngine(){
    terminate();
}

void PhysicsEngine::init(){}

void PhysicsEngine::terminate(){
    dynamicObjects_.clear();
    levelPtr_.reset();
}

void PhysicsEngine::update( double deltaT ){
    for( auto & o : dynamicObjects_ ){
        auto const& v = o->getCurrentVelocity();

        if( v > 0.0f ){
            auto const& pos = o->getCurrentPosition();
            auto const& dir = o->getCurrentDirection();
            auto newPos = pos + dir * v * float(deltaT);
            auto const& colliders = o->colliders();
            auto const& objectsToCheck = levelPtr_->obectsInArea( newPos, newPos + o->size() );
            o->setCurrentPosition( newPos );
        }
    }
}

void PhysicsEngine::add( std::shared_ptr< game::GameObjectInterface > obj ){
    dynamicObjects_.insert( obj );
}

void PhysicsEngine::setLevel( std::shared_ptr< game::Level > levelPtr ){
    levelPtr_ = levelPtr;
}

}// namespace phys