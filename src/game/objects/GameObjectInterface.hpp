#pragma once

// glm
#include "glm/glm.hpp"

// project
#include "../../phys/PhysicsEngine.hpp"

// std
#include <vector>

namespace game{
    class GameObjectInterface{
    public:// == TYPES ==
        enum class ObjectType{
            CONCRETE_WALL,
            BORDER,
            BRICK_WALL,
            BULLET,
            EAGLE,
            ICE,
            TANK,
            TREES,
            WATER,
            UNKNOWN
        };
    public:
        virtual ~GameObjectInterface(){}
        virtual void update( double deltaT ) = 0;
        virtual void render() const = 0;

        virtual glm::vec2 getCurrentPosition()const = 0;
        virtual void setCurrentPosition( glm::vec2 const& p ) = 0;

        virtual glm::vec2 getCurrentDirection()const = 0;
        virtual float getCurrentVelocity()const = 0;
        virtual void setVelocity( float v ) = 0;

        virtual std::vector< phys::AABB > const& colliders()const = 0;
        virtual glm::vec2 const& size()const = 0;
        virtual bool collides( ObjectType /*type*/ ) = 0;

        virtual void onCollision(){}

        virtual ObjectType objectType()const = 0;
    };

    class GameObject : public GameObjectInterface{
    protected:// == MEMBERS ==
        glm::vec2                   position_;
        glm::vec2                   size_;
        float                       rotationAngle_;
        float                       layer_{ 0.0f };
        glm::vec2                   direction_;
        float                       velocity_{0.0f};
        std::vector< phys::AABB >   colliders_;
        ObjectType                  eType_{ ObjectType::UNKNOWN };
    public:
        GameObject( ObjectType t, glm::vec2 const& pos, glm::vec2 const& sz, float angle, float layer )
        : position_( pos )
        , size_( sz )
        , rotationAngle_( angle )
        , layer_( layer )
        , direction_( 0.0f, 1.0f )
        , velocity_( 0.0f )
        , eType_( t )
        {}

        GameObject( GameObject const& ) = delete;
        GameObject& operator =( GameObject const& ) = delete;

        virtual ~GameObject(){}

        virtual void update( double /*deltaT*/ ) override{}

        virtual glm::vec2 getCurrentPosition()const override{
            return position_;
        }

        virtual void setCurrentPosition( glm::vec2 const& p ) override{
            position_ = p;
        }

        virtual glm::vec2 getCurrentDirection()const override{
            return direction_;
        }

        virtual float getCurrentVelocity()const override{
            return velocity_;
        }

        virtual void setVelocity( float v ) override{
            velocity_ = v;
        }

        virtual std::vector< phys::AABB > const& colliders()const override{
            return colliders_;
        }

        virtual glm::vec2 const& size()const override{
            return size_;
        }

        virtual ObjectType objectType()const override{
            return eType_;
        }      

        virtual bool collides( ObjectType /*type*/ ){
            return true;
        }
    };
}