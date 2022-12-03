#pragma once

// std
#include <array>
#include <memory>
// glm
#include "glm/vec2.hpp"

// project

namespace game{
    class Tank;
    class Level;
    class StartScreen;
}

class Game final{
public:// == TYPES ==
    enum class GameState{
        START_SCREEN,
        LEVEL_START,
        LEVEL,
        PAUSED,
        SCORES,
        GAME_OVER
    };
public:// == CONSTANTS ==
    static const int g_windowSizeX = 640;
    static const int g_windowSizeY = 480;
private:
    std::array< bool, 349 > keys_;
    GameState                               state_{ GameState::START_SCREEN };
    glm::ivec2                              windowSize_{ g_windowSizeX, g_windowSizeY };
    std::shared_ptr< game::Tank >           tankPtr_;
    std::shared_ptr< game::Level >          level0Ptr_;
    std::shared_ptr< game::StartScreen >    startScreenPtr_;
public:
    Game( glm::ivec2 const& size );
    ~Game();

    void update( double deltaT );
    void render();
    void setKey( int key, int action ){
        keys_.at( key ) = action;
    }
    bool initialize();

    size_t currentLevelWidth()const;
    size_t currentLevelHeight()const;
};