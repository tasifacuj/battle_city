#pragma once

// std
#include <memory>

namespace renderer{
    class Sprite;

    class SpriteAnimator{
        std::shared_ptr< Sprite >   spritePtr_;
        size_t                      frame_{0};
        double                      frameDuration_{0};
        double                      animationTime_{0};
        double                      totalDurationMS_{0.0};
    public:// == CTOR==
        SpriteAnimator( std::shared_ptr< Sprite > spritePtr );

    public:// == SpriteAnimator ==
        size_t getCurrentFrame()const{
            return frame_;
        }

        void update( double deltaT );

        /// @brief  calculate total time,required for all frames.
        /// @return sum of durations of all frames
        double getTotalDuration()const{
            return totalDurationMS_;
        }

        void reset();
    };
}