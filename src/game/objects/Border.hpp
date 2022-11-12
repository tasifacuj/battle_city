#pragma once

#include "GameObjectInterface.hpp"

// std
#include <memory>
#include <array>

namespace renderer{
    class Sprite;
}

namespace game{
    class Border : public GameObject{
    public:// == TYPES ==
        using SpritePtr = std::shared_ptr< renderer::Sprite >;
    private:
        SpritePtr   sprite_;
        
    public:
        Border( glm::vec2 const& pos, glm::vec2 const& sz, float angle, float layer );

    public:// == GameObjectInterface ==
        virtual void render() const override;
    };
}