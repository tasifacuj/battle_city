#pragma once

// std
#include <unordered_set>
#include <memory>

namespace game{
    class GameObjectInterface;
}

namespace phys{
    class PhysicsEngine{
        std::unordered_set< std::shared_ptr< game::GameObjectInterface > >  dynamicObjects_;
    private:
        PhysicsEngine() = default;
        PhysicsEngine(PhysicsEngine const&) = delete;
        PhysicsEngine& operator =(PhysicsEngine const&) = delete;
    public:// == CTOR ==
        ~PhysicsEngine();
        static PhysicsEngine& getInstance();

    public:// == PhysicsEngine ==
        void init();
        void terminate();
        void update( double deltaT );
        void add( std::shared_ptr< game::GameObjectInterface > obj );
    };
}