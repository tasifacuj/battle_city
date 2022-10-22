#pragma once

// std
#include <memory>

// glm
#include "glm/vec2.hpp"

namespace renderer{
    class AnimatedSprite;
}

namespace game{
    class Tank{
    public:// == TYPES ==
        enum class Orienation{
            Top,
            Bottom,
            Left,
            Right
        };

    private:
        Orienation                                  orient_;
        std::shared_ptr< renderer::AnimatedSprite > spritePtr_;
        bool                                        isMoving_{false};
        glm::vec2                                   position_;
        glm::vec2                                   moveOffset_;
        float                                       spd_;
    public:// == CTORs ==
        explicit Tank( std::shared_ptr< renderer::AnimatedSprite > sprite, float spd, glm::vec2 const& pos );

    public:// == Tank ==
        void render()const;
        
        void setOrient( Orienation orient );

        void move( bool move );

        void update( size_t deltaT );
    };
}