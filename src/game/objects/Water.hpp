#pragma once

#include "GameObjectInterface.hpp"
#include "../../renderer/SpriteAnimator.hpp"

// std
#include <memory>
#include <array>

namespace renderer{
    class Sprite;
}

namespace game{
    class Water : public GameObject{
    public:// == TYPES ==
        using SpritePtr = std::shared_ptr< renderer::Sprite >;
       
        enum Location{
            TOP_LEFT,
            TOP_RIGHT,
            BOTTOM_LEFT,
            BOTTOM_RIGHT
        };
    private:
        SpritePtr                   sprite_;
        renderer::SpriteAnimator    animator_;
        
    public:
        Water( glm::vec2 const& pos, glm::vec2 const& sz, float angle, float layer );

    public:// == GameObjectInterface ==
        virtual void update( double deltaT ) override;
        virtual void render() const override;

    private: // == BrickWall ==
        void renderBlock( Location loc )const;
    };
}