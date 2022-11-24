#pragma once

// std
#include <unordered_set>
#include <memory>

// glm
#include "glm/vec2.hpp"

namespace game{
    class GameObjectInterface;
    class Level;
}

namespace phys{
    // @brief Axis Aligned Bounding Box
    struct AABB{
        // AABB( glm::vec2 bl, glm::vec2 tr ) : bottomLeft( bl ), topRight( tr ){}
        glm::vec2 bottomLeft;
        glm::vec2 topRight;
    };

    class PhysicsEngine{
        std::unordered_set< std::shared_ptr< game::GameObjectInterface > >  dynamicObjects_;
        std::shared_ptr< game::Level >                                      levelPtr_;
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
        void setLevel( std::shared_ptr< game::Level > levelPtr );

    private:
        bool hasIntersection( std::vector< AABB > const& lshColliders, glm::vec2 const& lhsPos
                            , std::vector< AABB > const& rhsColliders, glm::vec2 const& rhsPos
                            );
    };
}