#pragma once

#include "GameObjectInterface.hpp"

// std
#include <memory>
#include <array>

namespace renderer{
    class Sprite;
}

namespace game{
    class BetonWall : public GameObject{
    public:// == TYPES ==
        using SpritePtr = std::shared_ptr< renderer::Sprite >;
        enum class WallType{
            ALL,
            TOP,
            BOTTOM,
            LEFT,
            RIGHT,
            TOP_LEFT,
            TOP_RIGHT,
            BOTTOM_LEFT,
            BOTTOM_RIGHT
        };

        enum class State{
            ENABLED,
            DESTROYED
        };

        enum Location{
            TOP_LEFT,
            TOP_RIGHT,
            BOTTOM_LEFT,
            BOTTOM_RIGHT
        };
    private:
        std::array< State, 4 >  currentState_;
        SpritePtr               sprite_;
        
    public:
        BetonWall( WallType wallType, glm::vec2 const& pos, glm::vec2 const& sz, float angle, float layer );

    public:// == GameObjectInterface ==
        virtual void update( double deltaT ) override;
        virtual void render() const override;

    private: // == BrickWall ==
        void renderBrick( Location loc )const;
    };
}