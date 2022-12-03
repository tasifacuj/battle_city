#pragma once

// std
#include <memory>
#include <vector>
#include <string>

// glm
#include "glm/vec2.hpp"

// project
#include "GameStateInterface.hpp"

namespace renderer{
    class Sprite;
}

namespace game{
    class StartScreen : public GameStateInterface{
        std::vector< std::pair< std::shared_ptr< renderer::Sprite >, glm::vec2 > > sprites_;
    public:// == CONSTANTS ==
        static constexpr unsigned BLOCK_SIZE = 8;
        static constexpr unsigned START_SCREEN_WIDTH    = 15 * BLOCK_SIZE * 2;
        static constexpr unsigned START_SCREEN_HEIGHT   = 14 * BLOCK_SIZE * 2;

    public:// == CTOR ==
        StartScreen( std::vector<std::string> const& description );

    public:// == GameStateInterface ==
        virtual void render()const override;
        virtual void update( double deltaT ) override;
        virtual unsigned getStateWidth()const override;
        virtual unsigned getStateHeight()const override;
    };
}