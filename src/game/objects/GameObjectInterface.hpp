#pragma once

// glm
#include "glm/glm.hpp"

namespace game{
    class GameObjectInterface{
    public:
        virtual ~GameObjectInterface(){}
        virtual void update( double deltaT ) = 0;
        virtual void render() const = 0;

        virtual glm::vec2 getCurrentPosition()const = 0;
        virtual void setCurrentPosition( glm::vec2 const& p ) = 0;

        virtual glm::vec2 getCurrentDirection()const = 0;
        virtual float getCurrentVelocity()const = 0;
        virtual void setVelocity( float v ) = 0;
    };

    class GameObject : public GameObjectInterface{
    protected:// == MEMBERS ==
        glm::vec2   position_;
        glm::vec2   size_;
        float       rotationAngle_;
        float       layer_{ 0.0f };
        glm::vec2   direction_;
        float       velocity_{0.0f};
    public:
        GameObject( glm::vec2 const& pos, glm::vec2 const& sz, float angle, float layer )
        : position_( pos )
        , size_( sz )
        , rotationAngle_( angle )
        , layer_( layer )
        , direction_( 0.0f, 1.0f )
        , velocity_( 0.0f )
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
    };
}