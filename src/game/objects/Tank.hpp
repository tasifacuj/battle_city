#pragma once

// std
#include <memory>

// glm
#include "glm/vec2.hpp"

#include "GameObjectInterface.hpp"

namespace renderer{
    class AnimatedSprite;
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
        Orienation                                  orient_;
        std::shared_ptr< renderer::AnimatedSprite > spritePtr_;
        bool                                        isMoving_{false};
        glm::vec2                                   moveOffset_;
        float                                       spd_;
    public:// == CTORs ==
        explicit Tank( std::shared_ptr< renderer::AnimatedSprite > sprite, float spd, glm::vec2 const& pos, glm::vec2 const& zize );

    public:// == RenderObjectInterface ==
        virtual void render()const override;
        virtual void update( size_t deltaT ) override;
    
    public:// == Tank ==
        void setOrient( Orienation orient );
        void move( bool move );
    };
}