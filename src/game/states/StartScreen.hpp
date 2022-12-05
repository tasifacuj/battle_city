#pragma once

// std
#include <memory>
#include <vector>
#include <string>

// glm
#include "glm/vec2.hpp"

// project
#include "GameStateInterface.hpp"
#include "renderer/SpriteAnimator.hpp"

class Game;

namespace renderer{
    class Sprite;
}

namespace game{
    class StartScreen : public GameStateInterface{
        int                                                                         currentMenuSelection_{0};
        std::vector< std::pair< std::shared_ptr< renderer::Sprite >, glm::vec2 > >  sprites_;
        std::pair< std::shared_ptr< renderer::Sprite >, glm::vec2 >                 menuSprite_;
        std::pair< std::shared_ptr< renderer::Sprite >, glm::vec2 >                 tankSprite_;
        renderer::SpriteAnimator                                                    tankAnimator_;
        Game&                                                                       game_;
        bool                                                                        keyWasReleased_{ true };
    public:// == CONSTANTS ==
        static constexpr unsigned BLOCK_SIZE = 8;
        static constexpr unsigned START_SCREEN_WIDTH    = 15 * BLOCK_SIZE * 2;
        static constexpr unsigned START_SCREEN_HEIGHT   = 14 * BLOCK_SIZE * 2;
        static constexpr unsigned MENU_WIDTH            = 128;
        static constexpr unsigned MENU_HEIGHT           = 64;
        static constexpr unsigned TANK_SIZE             = BLOCK_SIZE * 2;

    public:// == CTOR ==
        StartScreen( std::vector<std::string> const& description, Game& game );

    public:// == GameStateInterface ==
        virtual void render()const override;
        virtual void update( double deltaT ) override;
        virtual unsigned getStateWidth()const override;
        virtual unsigned getStateHeight()const override;
        virtual void processInput( std::array< bool, 349 > const& keys ) override;
    };
}