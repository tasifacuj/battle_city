#pragma once

// std
#include <unordered_set>
#include <memory>
#include <functional>

// glm
#include "glm/vec2.hpp"

namespace game{
    class GameObjectInterface;
    class Level;
}

namespace phys{
    enum class ECollisionDirection{
        Top,
        Bottom,
        Left,
        Right
    };

    /// @brief Axis Aligned Bounding Box
    struct AABB{
        // AABB( glm::vec2 bl, glm::vec2 tr ) : bottomLeft( bl ), topRight( tr ){}
        glm::vec2 bottomLeft;
        glm::vec2 topRight;
    };

    struct Collider{
        AABB boundingBox;
        bool isActive{false};
        std::function< void( game::GameObjectInterface const&, ECollisionDirection ) > onCollisionCallback;//!< 1-st param - object, that hits this collider,2-nd param -  direction where collision came from

    public:
        Collider( glm::vec2 const& bl, glm::vec2 const& tr, std::function< void( game::GameObjectInterface const&, ECollisionDirection ) > cb = {} )
        : boundingBox( AABB{ bl, tr } )
        , isActive( true )
        , onCollisionCallback( cb )
        {}

        Collider( AABB const& aabb, std::function< void( game::GameObjectInterface const&, ECollisionDirection ) > cb = {} )
        : boundingBox( aabb )
        , isActive( true )
        , onCollisionCallback( cb )
        {}
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
        bool hasIntersection( Collider const& lshCollider, glm::vec2 const& lhsPos, Collider const& rhsCollider, glm::vec2 const& rhsPos );
    };
}