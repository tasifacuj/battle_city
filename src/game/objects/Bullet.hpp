#pragma once

// project
#include "GameObjectInterface.hpp"
#include "../../renderer/SpriteAnimator.hpp"
#include "../../system/Timer.hpp"
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
        Orientation                         eOrient_{ Orientation::TOP };
        bool                                isActive_{ false };
        float                               maxVelocity_{0.0f};
        
        std::shared_ptr< renderer::Sprite > spriteExplosion_;
        renderer::SpriteAnimator            animatorExplosion_;
        glm::vec2                           explosionSize_;
        glm::vec2                           explosionOffset_;
        sys::Timer                          explosionTimer_;
        bool                                isExploding_{ false };
    public:// == CTOR ==
        Bullet( double velocity, glm::vec2 const& pos, glm::vec2 const& size, glm::vec2 const& exposionSize, float layer );

    public:// == GameObjectInterface ==
        virtual void render()const override;
        virtual void update( double deltaT ) override;
    public:// == Bullet ==
        bool isActive()const{
            return isActive_;
        }

        void fire( glm::vec2 const& position, glm::vec2 const& dir );
    };
}