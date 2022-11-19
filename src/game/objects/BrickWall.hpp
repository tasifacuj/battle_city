#pragma once

#include "GameObjectInterface.hpp"

// std
#include <memory>
#include <array>

namespace renderer{
    class Sprite;
}

namespace game{
    class BrickWall : public GameObject{
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

        enum class BrickState{
            ALL,
            TOP_LEFT,
            TOP_RIGHT,
            TOP,
            BOTTOM_LRFT,
            LEFT,
            TOP_RIGHT_BOTTOM_LEFT,
            TOP_BOTTOM_LEFT,
            BOTTOM_RIGHT,
            TOP_LEFT_BOTTOM_RIGHT,
            RIGHT,
            TOP_BOTTOM_RIGHT,
            BOTTOM,
            TOP_LEFT_BOTTOM,
            TOP_RIGHT_BOTTOM,
            DESTROYED
        };

        enum BrickLocation{
            TOP_LEFT,
            TOP_RIGHT,
            BOTTOM_LEFT,
            BOTTOM_RIGHT
        };
    private:
        std::array< BrickState, 4 > currentBrickState_;
        std::array< SpritePtr, 15 > sprites_;
        
    public:
        BrickWall( WallType wallType, glm::vec2 const& pos, glm::vec2 const& sz, float angle, float layer );

    public:// == GameObjectInterface ==
        virtual void update( double deltaT ) override;
        virtual void render() const override;

    private: // == BrickWall ==
        void renderBrick( BrickLocation loc )const;
    };
}