#include "Game.hpp"
#include "../renderer/ShaderProgram.hpp"
#include "../renderer/Texture2D.hpp"
#include "../renderer/Sprite.hpp"
#include "../resources/ResourceManager.hpp"
#include "objects/Tank.hpp"
#include "states/Level.hpp"
#include "../phys/PhysicsEngine.hpp"
#include "states/StartScreen.hpp"

// std
#include <iostream>
#include <chrono>

// glm
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


//glfw
#include "GLFW/glfw3.h"

Game::Game( glm::ivec2 const& size )
: windowSize_( size ){
    keys_.fill( false );
}

void Game::setWinfowSize( glm::ivec2 const& size ){
    windowSize_ = size;
    updateViewPort();
}

void Game::updateViewPort(){
    const float aspect_ratio = static_cast< float >( currentLevelWidth() ) / static_cast< float > ( currentLevelHeight() );
    GLint viewPortWidth = windowSize_.x;
    GLint viewPortHeight = windowSize_.y;
    GLint viewPortLeftOffset = 0;
    GLint viewPortBottomOffset = 0;

    if( static_cast<float>( windowSize_.x ) / windowSize_.y > aspect_ratio ){
        viewPortWidth = static_cast<int>( windowSize_.y * aspect_ratio );
        viewPortLeftOffset = static_cast<int>( (windowSize_.x - viewPortWidth) * 0.5f );
    }else{
        viewPortHeight = static_cast< int >( windowSize_.x / aspect_ratio );
        viewPortBottomOffset = static_cast<int>((windowSize_.y - viewPortHeight) * 0.5f);
    }

    glViewport( viewPortLeftOffset, viewPortBottomOffset, viewPortWidth, viewPortHeight);
    glm::mat4 projMatrix = glm::ortho( 0.0f, float( currentLevelWidth() ), 0.0f, float( currentLevelHeight() ), -100.0f, 100.0f );
    auto spriteProgramPtr = resources::ResourceManager::getInstance().getShaderProgram( "spriteShader" );
    spriteProgramPtr->use();
        spriteProgramPtr->setMatrix4( "projection", projMatrix );
}

Game::~Game(){}

bool Game::initialize(){
    resources::ResourceManager& resourceManager = resources::ResourceManager::getInstance();
    
    if( !resourceManager.loadJSONResources( "res/resources.json" ) ){
        std::cout << "Game failed to load resources" << std::endl;
        return false;
    }

    auto spriteProgramPtr = resourceManager.getShaderProgram( "spriteShader" );

    if( !spriteProgramPtr ){
        std::cout << "ERROR: No shader program spriteShader" << std::endl;
        return false;
    }

    gameStatePtr_ = std::make_shared< game::StartScreen >( resourceManager.getStartScreen(), *this );
    setWinfowSize( windowSize_ );

    return true;
}

void Game::update( double deltaT ){
    gameStatePtr_->processInput( keys_ );
    gameStatePtr_->update( deltaT );
    
    // switch(state_){
    //     case GameState::START_SCREEN:
    //         if( keys_[ GLFW_KEY_ENTER ] ){
    //             state_ = GameState::LEVEL;
    //             startNewLevel( 0 );
    //         }
    //     break;
    //     case GameState::LEVEL:
    //         gameStatePtr_->processInput( keys_ );
    //         gameStatePtr_->update( deltaT );
    //     break;
    // }
}

void Game::render(){
    gameStatePtr_->render();
}

void Game::startNewLevel( size_t levelId ){
    std::cout << "Starting level " << levelId << std::endl;
    auto& resm = resources::ResourceManager::getInstance();
    auto levelPtr = std::make_shared< game::Level >( resm.getLevels()[ levelId ] );
    phys::PhysicsEngine::getInstance().setLevel( levelPtr );
    gameStatePtr_ = levelPtr;
    updateViewPort();
}

size_t Game::currentLevelWidth()const{
    return gameStatePtr_->getStateWidth();
}

size_t Game::currentLevelHeight()const{
    return gameStatePtr_->getStateHeight();
}