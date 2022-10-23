#include "Game.hpp"
#include "../renderer/ShaderProgram.hpp"
#include "../renderer/Texture2D.hpp"
#include "../renderer/Sprite.hpp"
#include "../renderer/AnimatedSprite.hpp"
#include "../resources/ResourceManager.hpp"
#include "Tank.hpp"

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

    auto spriteProgramPtr = resourceManager.getShaderProgram( "sprites_shader" );

    if( !spriteProgramPtr ){
        std::cout << "ERROR: No shader program sprites_shader" << std::endl;
        return false;
    }


    glm::mat4 projMatrix = glm::ortho( 0.0f, float( windowSize_.x ), 0.0f, float( windowSize_.y ), -100.0f, 100.0f );
    spriteProgramPtr->use();
        spriteProgramPtr->setInt( "sampler", 0 );
        spriteProgramPtr->setMatrix4( "projection", projMatrix );


    {// tank
       
        auto tankSpritePtr = resourceManager.getAnimatedSprite( "TankAnimatedSprite" );

        if( !tankSpritePtr ){
            std::cout << "Failed to load tanks";
            return false;
        }
        
        // renderer::AnimatedSprite::FrameVec tankTopFrames{
        //     { "yellowType1_Top1", 500'000'000 },
        //     { "yellowType1_Top2", 500'000'000}
        // };
        
        // renderer::AnimatedSprite::FrameVec tankLeftFrames{
        //     { "yellowType1_Left1", 500'000'000 },
        //     { "yellowType1_Left2", 500'000'000}
        // };
        
        // renderer::AnimatedSprite::FrameVec tankBottomFrames{
        //     { "yellowType1_Bottom1", 500'000'000 },
        //     { "yellowType1_Bottom2", 500'000'000 }
        // };

        // renderer::AnimatedSprite::FrameVec tankRightFrames{
        //     { "yellowType1_Right1", 500'000'000  },
        //     { "yellowType1_Right2", 500'000'000 }
        // };

        // tankSpritePtr->addState( "tankTopState", tankTopFrames );
        // tankSpritePtr->addState( "tankBottomState", tankBottomFrames );
        // tankSpritePtr->addState( "tankLeftState", tankLeftFrames );
        // tankSpritePtr->addState( "tankRightState", tankRightFrames );
        
        tankSpritePtr->setState( "tankTopState" );
        tankPtr_ = std::make_unique< game::Tank >( tankSpritePtr, 0.0000001f, glm::vec2( 100.0f, 100.0f ) );
    }

    return true;
}

void Game::update( size_t deltaT ){
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
}