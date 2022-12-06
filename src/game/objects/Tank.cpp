#include "Tank.hpp"
#include "../../renderer/Sprite.hpp"
#include "../../resources/ResourceManager.hpp"
#include "Bullet.hpp"
#include "../AIComponent.hpp"

namespace game{
Tank::Tank( Tank::ETankType eType, bool hasAI, bool hasShield, Orienation orient, float spd, glm::vec2 const& pos, glm::vec2 const& size, float layer )
: GameObject( ObjectType::TANK, pos, size, 0.0f, layer )
, orient_( orient )
, spriteTop_( resources::ResourceManager::getInstance().getSprite( getTankSpriteFromType(eType) + "_top" ) )
, spriteBottom_( resources::ResourceManager::getInstance().getSprite( getTankSpriteFromType(eType) + "_bottom" ) )
, spriteLeft_( resources::ResourceManager::getInstance().getSprite(getTankSpriteFromType(eType) + "_left" ) )
, spriteRight_( resources::ResourceManager::getInstance().getSprite(getTankSpriteFromType(eType) + "_right" ) )
, maxAllowedSpd_( spd )
, animatorTop_( spriteTop_ )
, animatorBottom_( spriteBottom_ )
, animatorLeft_( spriteLeft_ )
, animatorRight_( spriteRight_ )
, spriteRespawn_( resources::ResourceManager::getInstance().getSprite( "respawn" ) )
, respawnAnimator_( spriteRespawn_ )
, spriteShield_( resources::ResourceManager::getInstance().getSprite( "shield" ) )
, shieldAnimator_( spriteShield_ )
, bulletPtr_( std::make_shared< Bullet >( 0.15f, position_, size_ / 2.0f, size_, layer )){
    setOrient( orient );
    isSpawning_ = true;
    respawnTimer_.setCallback( [this, hasShield](){
        isSpawning_ = false;
        if( aiPtr_ ) setVelocity( maxAllowedSpd_ );
        hasShield_ = hasShield;

        if( hasShield )
            shieldTimer_.start( 2000 );
    } );

    respawnTimer_.start( 1000 );

    shieldTimer_.setCallback( [this](){
        hasShield_ = false;
    } );

    colliders_.emplace_back( phys::AABB{glm::vec2(0.0f, 0.0f),  size_} );
    phys::PhysicsEngine::getInstance().add( bulletPtr_ );

    if( hasAI ){
        aiPtr_ = std::make_unique< AIComponent >( *this );
    }
}

void Tank::update( double deltaT ){
    if( bulletPtr_->isActive() ){
        bulletPtr_->update( deltaT );
    }

    if( isSpawning_ ){
        respawnAnimator_.update( deltaT );
        respawnTimer_.update( deltaT );
        return;
    }

    if( aiPtr_ ) aiPtr_->update( deltaT );

    if( hasShield_ ){
        shieldAnimator_.update( deltaT );
        shieldTimer_.update( deltaT );
    }

    if( velocity_> 0.0 ){     
        switch (orient_)
        {
        case Orienation::Top:
            animatorTop_.update( deltaT );
            break;
        case Orienation::Bottom:
            animatorBottom_.update( deltaT );
            break;
        case Orienation::Left:
            animatorLeft_.update( deltaT );
            break;
        case Orienation::Right:
            animatorRight_.update( deltaT );
            break;

        default:
            break;
        }
    }
}

void Tank::render()const{
    if( isSpawning_ ){
        spriteRespawn_->render( position_, size_, rotationAngle_, layer_, respawnAnimator_.getCurrentFrame() );
    }else{
        switch (orient_){
        case Tank::Orienation::Top:
            spriteTop_->render( position_, size_, rotationAngle_, layer_ ,  animatorTop_.getCurrentFrame() );
            break;

        case Tank::Orienation::Bottom:
            spriteBottom_->render( position_, size_, rotationAngle_, layer_, animatorBottom_.getCurrentFrame() );
            break;

        case Tank::Orienation::Left:
            spriteLeft_->render( position_, size_, rotationAngle_, layer_, animatorLeft_.getCurrentFrame() );
            break;

        case Tank::Orienation::Right:
            spriteRight_->render( position_, size_, rotationAngle_, layer_, animatorRight_.getCurrentFrame() );
            break;
        
        default:
            break;
        }

        if( hasShield_ ){
            spriteShield_->render( position_, size_, rotationAngle_, layer_ + 0.1f, shieldAnimator_.getCurrentFrame() );
        }

        if( bulletPtr_->isActive() ) bulletPtr_->render();
    }

    
}

void Tank::setOrient( Tank::Orienation orient ){
    // if( orient_ == orient ) return;

    orient_ = orient;

    switch (orient_)
    {
    case Tank::Orienation::Top:
        direction_ = glm::vec2( 0.0f, 1.0f );
        break;

    case Tank::Orienation::Bottom:
        direction_ = glm::vec2( 0.0f, -1.0f );
        break;

    case Tank::Orienation::Left:
        direction_ = glm::vec2( -1.0f, 0.0f );
        break;

    case Tank::Orienation::Right:
        direction_ = glm::vec2( 1.0f, 0.0f );
        break;
    
    default:
        break;
    }
}

void Tank::setVelocity( float v ){
    if( false == isSpawning_ ){
        GameObject::setVelocity( v );
    }
}

void Tank::fire(){
    if( !isSpawning_ && !bulletPtr_->isActive() )
        bulletPtr_->fire( position_ + size_ / 4.0f, direction_ );
}

const std::string& Tank::getTankSpriteFromType(const Tank::ETankType eType){
    return TankTypeToSpriteString[static_cast<size_t>(eType)];
}

}