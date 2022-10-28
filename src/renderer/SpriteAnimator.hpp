#pragma once

// std
#include <memory>

namespace renderer{
    class Sprite;

    class SpriteAnimator{
        std::shared_ptr< Sprite >   spritePtr_;
        size_t                      frame_{0};
        size_t                      frameDuration_{0};
        size_t                      animationTime_{0};
    public:// == CTOR==
        SpriteAnimator( std::shared_ptr< Sprite > spritePtr );

    public:// == SpriteAnimator ==
        size_t getCurrentFrame()const{
            return frame_;
        }

        void update( size_t deltaT );

    };
}