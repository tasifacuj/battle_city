#pragma once

#include "GameObjectInterface.hpp"

// std
#include <memory>

namespace renderer{
    class Sprite;
}

namespace game{
    class BrickWall : public GameObject{
        std::shared_ptr< renderer::Sprite > spritePtr_;
    public:
        BrickWall( std::shared_ptr< renderer::Sprite > spritePtr, glm::vec2 const& pos, glm::vec2 const& sz, float angle );

    public:
        virtual void update( size_t deltaT ) override;
        virtual void render() const override;
    };
}