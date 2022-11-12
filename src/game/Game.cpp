#include "Game.hpp"
#include "../renderer/ShaderProgram.hpp"
#include "../renderer/Texture2D.hpp"
#include "../renderer/Sprite.hpp"
#include "../resources/ResourceManager.hpp"
#include "objects/Tank.hpp"
#include "Level.hpp"

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


    glm::mat4 projMatrix = glm::ortho( 0.0f, float( windowSize_.x ), 0.0f, float( windowSize_.y ), -100.0f, 100.0f );
    spriteProgramPtr->use();
        spriteProgramPtr->setInt( "sampler", 0 );
        spriteProgramPtr->setMatrix4( "projection", projMatrix );


    {// tank
       
        // tankSpritePtr->setState( "tankTopState" );
        tankPtr_ = std::make_unique< game::Tank >( 
            resourceManager.getSprite( "tankSprite_top" )
            , resourceManager.getSprite( "tankSprite_bottom" )
            , resourceManager.getSprite( "tankSprite_left" )
            , resourceManager.getSprite( "tankSprite_right" )
            , 0.00000006f
            , glm::vec2( 0.0f, 0.0f )
            , glm::vec2( 16.0f, 16.0f ) );
        level0Ptr_ = std::make_unique< game::Level >( resourceManager.getLevels()[1] );
    }

    return true;
}

void Game::update( size_t deltaT ){
    if( level0Ptr_ ){
        level0Ptr_->update( deltaT );
    }

    if( tankPtr_ ){
        if( keys_[ GLFW_KEY_W ] ){
            tankPtr_->setOrient( game::Tank::Orienation::Top );
            tankPtr_->move( true );
        }else if( keys_[ GLFW_KEY_A ] ){
            tankPtr_->setOrient( game::Tank::Orienation::Left );
            tankPtr_->move( true );
        }else if( keys_[ GLFW_KEY_S ] ){
            tankPtr_->setOrient( game::Tank::Orienation::Bottom );
            tankPtr_->move( true );
        }else if( keys_[ GLFW_KEY_D ] ){
            tankPtr_->setOrient( game::Tank::Orienation::Right );
            tankPtr_->move( true );
        }else{
            tankPtr_->move( false );
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