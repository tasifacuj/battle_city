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
    auto programPtr = resourceManager.loadShaders( "default", "res/shaders/vertex.txt", "res/shaders/fragment.txt" );

    if( !programPtr ){
        return false;
    }

    auto spriteProgramPtr = resourceManager.loadShaders( "sprites_shader", "res/shaders/sprite.vert", "res/shaders/sprite.frag" );

    if( !spriteProgramPtr ){
        return false;
    }

    auto texPtr = resourceManager.loadTexture( "default", "res/textures/map_16x16.png" );
    std::vector<std::string> subNames{
        "block",
        "topBlock",
        "bottomBlock",
        "leftBlock",
        "rightBlock",
        "topLeftBlock",
        "topRightBlock",
        "bottomLeftBlock",

        "bottomRightBlock",
        "concrete",
        "topConcrete",
        "bottomConcreate",
        "leftConcrete",
        "rightConcrete",
        "topLeftConcrete",
        "topRightConcrete",
        
        "bottomLeftConcrete",
        "bottomRightConcrete",
        "water1",
        "water2",
        "water3",
        "trees",
        "ice",
        "wall",

        "eagle",
        "deadEagle",
        "nothing",
        "reaspawn1",
        "reaspawn2",
        "reaspawn3",
        "reaspawn4",
    };
    resourceManager.loadTextureAtlas( "TexAtlas", "res/textures/map_16x16_.png", 16, 16, subNames );
    auto spritePtr = resourceManager.loadSprite( "default", "TexAtlas", "sprites_shader", 100 ,100, "concrete" );

    if( !spritePtr ){
        std::cout << "Failed to load defaut sprite"  << std::endl;
        return false;
    }

    spritePtr->setPosition( glm::vec2( 190, 100 ) );

    auto animatedSpritePtr = resourceManager.loadAnimatedSprite( "animated_sprite", "TexAtlas", "sprites_shader", 100 ,100, "concrete" );
    animatedSpritePtr->setPosition( glm::vec2( 300, 300 ) );
    renderer::AnimatedSprite::FrameVec waterFrames{
        { "water1", 1000'000'000 },
        { "water2", 1000'000'000 },
        { "water3", 1000'000'000 },
    };

    renderer::AnimatedSprite::FrameVec eagleFrames{
        { "eagle", 1000'000'000 },
        { "deadEagle", 1000'000'000 }
    };

    animatedSpritePtr->addState( "waterState", waterFrames );
    animatedSpritePtr->addState( "eagleState", eagleFrames );
    animatedSpritePtr->setState( "waterState" );

    programPtr->use();
        programPtr->setInt( "sampler", 0 );// use texture loaded into GL_TEXTURE_0
        
        glm::mat4 model( 1.0f );
        model = glm::translate( model, glm::vec3( 100.0f, 200.0f, 0.0f ) );
        glm::mat4 model2 = glm::translate( glm::mat4( 1.0f ), glm::vec3( 590.0f, 50.0f, 0.0f ) );

        glm::mat4 projMatrix = glm::ortho( 0.0f, float( windowSize_.x ), 0.0f, float( windowSize_.y ), -100.0f, 100.0f );
        programPtr->setMatrix4( "projection", projMatrix );

    spriteProgramPtr->use();
        spriteProgramPtr->setInt( "sampler", 0 );
        spriteProgramPtr->setMatrix4( "projection", projMatrix );


    {// tank
        std::vector<std::string> subTankNames{
            "tankTop1",
            "tankTop2",
            "tankLeft1",
            "tankLeft2",
            "tankBottom1",
            "tankBottom2",
            "tankRight1",
            "tankRight2",
        };
        resourceManager.loadTextureAtlas( "TankTexAtlas", "res/textures/tanks.png", 16, 16, subTankNames );
        auto tankSpritePtr = resourceManager.loadAnimatedSprite( "tank_sprite", "TankTexAtlas", "sprites_shader", 100 ,100, "tankTop1" );
        
        renderer::AnimatedSprite::FrameVec tankTopFrames{
            { "tankTop1", 500'000'000 },
            { "tankTop2", 500'000'000}
        };
        
        renderer::AnimatedSprite::FrameVec tankLeftFrames{
            { "tankLeft1", 500'000'000 },
            { "tankLeft2", 500'000'000}
        };
        
        renderer::AnimatedSprite::FrameVec tankBottomFrames{
            { "tankBottom1", 500'000'000 },
            { "tankBottom2", 500'000'000 }
        };

        renderer::AnimatedSprite::FrameVec tankRightFrames{
            { "tankRight1", 500'000'000  },
            { "tankRight2", 500'000'000 }
        };

        tankSpritePtr->addState( "tankTopState", tankTopFrames );
        tankSpritePtr->addState( "tankBottomState", tankBottomFrames );
        tankSpritePtr->addState( "tankLeftState", tankLeftFrames );
        tankSpritePtr->addState( "tankRightState", tankRightFrames );
        
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