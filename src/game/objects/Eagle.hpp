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
    class Eagle : public GameObject{
    public:// == TYPES ==
        using SpritePtr = std::shared_ptr< renderer::Sprite >;
    private:
        SpritePtr                   sprite_;
        SpritePtr                   deadsprite_;
        bool                        alive_{true};
    public:
        Eagle( glm::vec2 const& pos, glm::vec2 const& sz, float angle );

    public:// == GameObjectInterface ==
        virtual void render() const override;

    };
}