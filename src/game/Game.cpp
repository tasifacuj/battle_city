#include "Game.hpp"
#include "../renderer/ShaderProgram.hpp"
#include "../renderer/Texture2D.hpp"
#include "../renderer/Sprite.hpp"
#include "../resources/ResourceManager.hpp"
#include "objects/Tank.hpp"
#include "Level.hpp"
#include "../phys/PhysicsEngine.hpp"

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

    level0Ptr_ = std::make_shared< game::Level >( resourceManager.getLevels()[0] );
    auto& pheng = phys::PhysicsEngine::getInstance();
    pheng.setLevel( level0Ptr_ );
    windowSize_.x = static_cast<int>( level0Ptr_->width() );
    windowSize_.y = static_cast<int>( level0Ptr_->height() );
    glm::mat4 projMatrix = glm::ortho( 0.0f, float( windowSize_.x ), 0.0f, float( windowSize_.y ), -100.0f, 100.0f );
    spriteProgramPtr->use();
        spriteProgramPtr->setInt( "sampler", 0 );
        spriteProgramPtr->setMatrix4( "projection", projMatrix );


    {// tank
       
        // tankSpritePtr->setState( "tankTopState" );
        tankPtr_ = std::make_shared< game::Tank >( 
            resourceManager.getSprite( "tankSprite_top" )
            , resourceManager.getSprite( "tankSprite_bottom" )
            , resourceManager.getSprite( "tankSprite_left" )
            , resourceManager.getSprite( "tankSprite_right" )
            , 0.05f
            , level0Ptr_->player1Respawn()
            , glm::vec2( game::Level::TILE_SIZE, game::Level::TILE_SIZE )
            , 0.0f );
        
    }

    pheng.add( tankPtr_ );
    return true;
}

void Game::update( double deltaT ){
    if( level0Ptr_ ){
        level0Ptr_->update( deltaT );
    }

    if( tankPtr_ ){
        if( keys_[ GLFW_KEY_W ] ){
            tankPtr_->setOrient( game::Tank::Orienation::Top );
            tankPtr_->setVelocity( tankPtr_->getMaxAllowedSpd() );
        }else if( keys_[ GLFW_KEY_A ] ){
            tankPtr_->setOrient( game::Tank::Orienation::Left );
            tankPtr_->setVelocity( tankPtr_->getMaxAllowedSpd() );
        }else if( keys_[ GLFW_KEY_S ] ){
            tankPtr_->setOrient( game::Tank::Orienation::Bottom );
            tankPtr_->setVelocity( tankPtr_->getMaxAllowedSpd() );
        }else if( keys_[ GLFW_KEY_D ] ){
            tankPtr_->setOrient( game::Tank::Orienation::Right );
            tankPtr_->setVelocity( tankPtr_->getMaxAllowedSpd() );
        }else{
            tankPtr_->setVelocity( 0.0f );
        }

        tankPtr_->update( deltaT );
    }
}

void Game::render(){
    if( tankPtr_ ){
        tankPtr_->render();
    }

    if( level0Ptr_ ){
        level0Ptr_->render();
    }
}

size_t Game::currentLevelWidth()const{
    return level0Ptr_->width();
}

size_t Game::currentLevelHeight()const{
    return level0Ptr_->height();
}