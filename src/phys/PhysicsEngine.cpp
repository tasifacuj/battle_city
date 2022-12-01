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
            ECollisionDirection dynCollDir = ECollisionDirection::Right;

            if( dir.x < 0.0f ) dynCollDir = ECollisionDirection::Left;
            else if( dir.y > 0.0f ) dynCollDir = ECollisionDirection::Top;
            else if( dir.y < 0.0f ) dynCollDir = ECollisionDirection::Bottom;

            ECollisionDirection objColldir = ECollisionDirection::Left;

            if( dir.x < 0.0f ) objColldir = ECollisionDirection::Right;
            else if( dir.y > 0.0f ) objColldir = ECollisionDirection::Bottom;
            else if( dir.y < 0.0f ) objColldir = ECollisionDirection::Top;

            for( auto const& dynObjCollider : colliders ){
                for( const auto& objToCheck : objectsToCheck ){
                    const auto& ccollidersToCheck = objToCheck->colliders();
                
                    if( objToCheck->collides( o->objectType() ) && !ccollidersToCheck.empty() ){
                        for( auto const& currentObjectCollider : ccollidersToCheck ){
                            if( currentObjectCollider.isActive && hasIntersection( dynObjCollider, newPos, currentObjectCollider, objToCheck->getCurrentPosition() ) ){
                                hasCollision = true;
                                //    wall                                                                                 o == bullet                
                                if( currentObjectCollider.onCollisionCallback ) currentObjectCollider.onCollisionCallback( *o, objColldir );//wall affected by bullet
                                //   bullet                                                                    wall
                                if( dynObjCollider.onCollisionCallback ) dynObjCollider.onCollisionCallback( *objToCheck, dynCollDir );// bullet affected by wall
                                break;
                            }
                        }
                    }
                }
            }

            if( !hasCollision ){
                o->setCurrentPosition( newPos );
            }
            else{
                // alighn position to multiple of 8 pixels.
                if( dir.x != 0.0f ) o->setCurrentPosition( glm::vec2( pos.x, static_cast< int >( pos.y / 4 + 0.5f ) * 4 ) );
                else if( dir.y != 0.0f ) o->setCurrentPosition( glm::vec2( static_cast< int>( pos.x / 4 + 0.5f ) * 4, pos.y ) );
            }
        }
    }
}

void PhysicsEngine::add( std::shared_ptr< game::GameObjectInterface > obj ){
    dynamicObjects_.insert( obj );
}

void PhysicsEngine::setLevel( std::shared_ptr< game::Level > levelPtr ){
    levelPtr_ = levelPtr;
}

bool PhysicsEngine::hasIntersection( Collider const& lhsCollider, glm::vec2 const& lhsPos, Collider const& rhsCollider, glm::vec2 const& rhsPos ){
    glm::vec2 lhsBottomLeftWorld = lhsCollider.boundingBox.bottomLeft + lhsPos;
    glm::vec2 lhsTopRightWorld = lhsCollider.boundingBox.topRight + lhsPos;
    
    
    glm::vec2 rhsBottomLeftWorld = rhsCollider.boundingBox.bottomLeft + rhsPos;
    glm::vec2 rhsTopRightWorld = rhsCollider.boundingBox.topRight + rhsPos;

    if( lhsBottomLeftWorld.x >= rhsTopRightWorld.x ) return false;
    if( lhsTopRightWorld.x <= rhsBottomLeftWorld.x ) return false;
    if( lhsBottomLeftWorld.y >= rhsTopRightWorld.y ) return false;
    if( lhsTopRightWorld.y <= rhsBottomLeftWorld.y ) return false;

    return true;
}

}// namespace phys