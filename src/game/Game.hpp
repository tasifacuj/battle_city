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
}

class Game final{
public:// == TYPES ==
    enum class GameState{
        ACTIVE,
        PAUSED
    };
public:// == CONSTANTS ==
    static const int g_windowSizeX = 640;
    static const int g_windowSizeY = 480;
private:
    std::array< bool, 349 > keys_;
    GameState                       state_{ GameState::ACTIVE };
    glm::ivec2                      windowSize_{ g_windowSizeX, g_windowSizeY };
    std::unique_ptr< game::Tank >   tankPtr_;
    std::unique_ptr< game::Level >  level0Ptr_;
public:
    Game( glm::ivec2 const& size );
    ~Game();

    void update( size_t deltaT );
    void render();
    void setKey( int key, int action ){
        keys_.at( key ) = action;
    }
    bool initialize();
};