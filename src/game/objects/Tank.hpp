#pragma once

// std
#include <memory>

// glm
#include "glm/vec2.hpp"

// project
#include "GameObjectInterface.hpp"
#include "../../renderer/SpriteAnimator.hpp"

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

    private:
        Orienation                          orient_;

        std::shared_ptr< renderer::Sprite > spriteTop_;
        std::shared_ptr< renderer::Sprite > spriteBottom_;
        std::shared_ptr< renderer::Sprite > spriteLeft_;
        std::shared_ptr< renderer::Sprite > spriteRight_;
        
        bool                                isMoving_{false};
        glm::vec2                           moveOffset_;
        float                               spd_;

        renderer::SpriteAnimator            animatorTop_;
        renderer::SpriteAnimator            animatorBottom_;
        renderer::SpriteAnimator            animatorLeft_;
        renderer::SpriteAnimator            animatorRight_;

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
        virtual void update( size_t deltaT ) override;
    
    public:// == Tank ==
        void setOrient( Orienation orient );
        void move( bool move );
    };
}