#pragma once

// glm
#include "glm/glm.hpp"

namespace game{
    class GameObjectInterface{
    public:
        virtual ~GameObjectInterface(){}
        virtual void update( size_t deltaT ) = 0;
        virtual void render() const = 0;
    };

    class GameObject : public GameObjectInterface{
    protected:
        glm::vec2   position_;
        glm::vec2   size_;
        float       rotationAngle_;
    public:
        GameObject( glm::vec2 const& pos, glm::vec2 const& sz, float angle )
        : position_( pos )
        , size_( sz )
        , rotationAngle_( angle )
        {}

        GameObject( GameObject const& ) = delete;
        GameObject& operator =( GameObject const& ) = delete;

        virtual ~GameObject(){}
    };
}