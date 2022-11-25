#pragma once

// project
#include "GameObjectInterface.hpp"

// std
#include <memory>

namespace renderer{
    class Sprite;
}

namespace game{
    class Bullet : public GameObject{
    public:// == TYPES ==
        enum class Orientation : uint8_t{
            TOP,
            BOTTOM,
            LEFT,
            RIGHT
        };

    private:// == MEMBERS ==
        std::shared_ptr< renderer::Sprite > spriteTop_;
        std::shared_ptr< renderer::Sprite > spriteBottom_;
        std::shared_ptr< renderer::Sprite > spriteLeft_;
        std::shared_ptr< renderer::Sprite > spriteRight_;
        Orientation eOrient_{ Orientation::TOP };
        bool isActive_{ false };

    public:// == CTOR ==
        Bullet( double velocity, glm::vec2 const& pos, glm::vec2 const& size, float layer );

    public:// == GameObjectInterface ==
        virtual void render()const override;

    public:// == Bullet ==
        bool isActive()const{
            return isActive_;
        }

        void fire( glm::vec2 const& position, glm::vec2 const& dir );
    };
}