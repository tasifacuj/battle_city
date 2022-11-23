#pragma once

// std
#include <memory>

// glm
#include "glm/vec2.hpp"

// project
#include "GameObjectInterface.hpp"
#include "../../renderer/SpriteAnimator.hpp"
#include "../../system/Timer.hpp"

namespace renderer{
    class Sprite;
}

namespace game{
    class Tank : public GameObject{
    public:// == TYPES ==
        enum class Orienation{
            Top,
            Bottom,
            Left,
            Right
        };

        using SpritePtr = std::shared_ptr< renderer::Sprite >;
    private:
        Orienation                          orient_;

        std::shared_ptr< renderer::Sprite > spriteTop_;
        std::shared_ptr< renderer::Sprite > spriteBottom_;
        std::shared_ptr< renderer::Sprite > spriteLeft_;
        std::shared_ptr< renderer::Sprite > spriteRight_;
        
        float                               maxAllowedSpd_;

        renderer::SpriteAnimator            animatorTop_;
        renderer::SpriteAnimator            animatorBottom_;
        renderer::SpriteAnimator            animatorLeft_;
        renderer::SpriteAnimator            animatorRight_;


        SpritePtr                           spriteRespawn_;
        renderer::SpriteAnimator            respawnAnimator_;
        bool                                isSpawning_{ true };

        SpritePtr                           spriteShield_;
        renderer::SpriteAnimator            shieldAnimator_;
        bool                                hasShield_{ false };

        sys::Timer                          respawnTimer_;
        sys::Timer                          shieldTimer_;
    public:// == CTORs ==
        explicit Tank( std::shared_ptr< renderer::Sprite > spriteTop
        , std::shared_ptr< renderer::Sprite > spriteBottom
        , std::shared_ptr< renderer::Sprite > spriteLeft
        , std::shared_ptr< renderer::Sprite > spriteRight
        , float spd
        , glm::vec2 const& pos
        , glm::vec2 const& zize
        , float layer );

    public:// == RenderObjectInterface ==
        virtual void render()const override;
        virtual void update( double deltaT ) override;
        virtual void setVelocity( float v ) override;
    public:// == Tank ==
        void setOrient( Orienation orient );
        
        float getMaxAllowedSpd()const{
            return maxAllowedSpd_;
        }
    };
}