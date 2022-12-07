#pragma once

// std
#include <array>
#include <memory>
// glm
#include "glm/vec2.hpp"

// project

namespace game{
    class GameStateInterface;
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

    enum class GameMode{
        SINGLE_PLAYER,
        TWO_PLAYERS
    };
public:// == CONSTANTS ==
    static const int g_windowSizeX = 640;
    static const int g_windowSizeY = 480;
private:
    std::array< bool, 349 > keys_;
    GameState                                   state_{ GameState::START_SCREEN };
    glm::ivec2                                  windowSize_{ g_windowSizeX, g_windowSizeY };
    std::shared_ptr< game::GameStateInterface>  gameStatePtr_;
    size_t                                      levelIdx_{0};
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
    void setWinfowSize( glm::ivec2 const& size );
    void startNewLevel( size_t levelId, GameMode mode );
    void nextLevel( GameMode mode );
private:
    void updateViewPort();
};