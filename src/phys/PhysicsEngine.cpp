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

            // alighn position to multiple of 8 pixels.
            if( dir.x != 0.0f ) o->setCurrentPosition( glm::vec2( pos.x, static_cast< int >( pos.y / 4 + 0.5f ) * 4 ) );
            else if( dir.y != 0.0f ) o->setCurrentPosition( glm::vec2( static_cast< int>( pos.x / 4 + 0.5f ) * 4, pos.y ) );

            auto newPos = pos + dir * v * float(deltaT);
            auto const& colliders = o->colliders();
            auto const& objectsToCheck = levelPtr_->obectsInArea( newPos, newPos + o->size() );
            bool hasCollision = false;

            for( const auto& o : objectsToCheck ){
                const auto& ccollidersToCheck = o->colliders();
                
                if( !ccollidersToCheck.empty() ){
                    if( hasIntersection( colliders, newPos, ccollidersToCheck, o->getCurrentPosition() ) ){
                        hasCollision = true;
                        break;
                    }
                }
            }

            if( !hasCollision ){
                o->setCurrentPosition( newPos );
            }
            // else{
            //     // alighn position to multiple of 8 pixels.
            //     if( dir.x != 0.0f ) o->setCurrentPosition( glm::vec2( pos.x, static_cast< int >( pos.y / 4 + 0.5f ) * 4 ) );
            //     else if( dir.y != 0.0f ) o->setCurrentPosition( glm::vec2( static_cast< int>( pos.x / 4 + 0.5f ) * 4, pos.y ) );
            // }
        }
    }
}

void PhysicsEngine::add( std::shared_ptr< game::GameObjectInterface > obj ){
    dynamicObjects_.insert( obj );
}

void PhysicsEngine::setLevel( std::shared_ptr< game::Level > levelPtr ){
    levelPtr_ = levelPtr;
}

bool PhysicsEngine::hasIntersection( std::vector< AABB > const& lshColliders, glm::vec2 const& lhsPos, std::vector< AABB > const& rhsColliders, glm::vec2 const& rhsPos){
    for( auto const& lhs : lshColliders ){
        glm::vec2 lhsBottomLeftWorld = lhs.bottomLeft + lhsPos;
        glm::vec2 lhsTopRightWorld = lhs.topRight + lhsPos;
        
        for( auto const& rhs : rhsColliders ){
            glm::vec2 rhsBottomLeftWorld = rhs.bottomLeft + rhsPos;
            glm::vec2 rhsTopRightWorld = rhs.topRight + rhsPos;

            if( lhsBottomLeftWorld.x >= rhsTopRightWorld.x ) return false;
            if( lhsTopRightWorld.x <= rhsBottomLeftWorld.x ) return false;
            if( lhsBottomLeftWorld.y >= rhsTopRightWorld.y ) return false;
            if( lhsTopRightWorld.y <= rhsBottomLeftWorld.y ) return false;
        }
    }

    return true;
}

}// namespace phys