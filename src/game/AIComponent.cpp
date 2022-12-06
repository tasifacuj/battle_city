#include "AIComponent.hpp"
#include "objects/Tank.hpp"

namespace game{
AIComponent::AIComponent( game::Tank& tank ) : tank_( tank ){}

void AIComponent::update( double deltaT ){
    tank_.fire();
}

}