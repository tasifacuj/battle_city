#pragma once

// glm
#include "glm/glm.hpp"

namespace game{
    class GameObjectInterface{
    public:
        virtual ~GameObjectInterface(){}
        virtual void update( double deltaT ) = 0;
        virtual void render() const = 0;
    };

    class GameObject : public GameObjectInterface{
    protected:
        glm::vec2   position_;
        glm::vec2   size_;
        float       rotationAngle_;
        float       layer_{ 0.0f };
    public:
        GameObject( glm::vec2 const& pos, glm::vec2 const& sz, float angle, float layer )
        : position_( pos )
        , size_( sz )
        , rotationAngle_( angle )
        , layer_( layer )
        {}

        GameObject( GameObject const& ) = delete;
        GameObject& operator =( GameObject const& ) = delete;

        virtual ~GameObject(){}

        virtual void update( double /*deltaT*/ ) override{}
    };
}