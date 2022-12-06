#pragma once

// std
#include <memory>

// glm
#include "glm/vec2.hpp"

// project
#include "GameObjectInterface.hpp"
#include "../../renderer/SpriteAnimator.hpp"
#include "../../system/Timer.hpp"

namespace renderer{
    class Sprite;
}

namespace game{
    class Bullet;
    class AIComponent;

    class Tank : public GameObject{
    public:// == TYPES ==
        enum class Orienation{
            Top,
            Bottom,
            Left,
            Right
        };

        using SpritePtr = std::shared_ptr< renderer::Sprite >;

        enum class ETankType : uint8_t{
            Player1Yellow_type1,
            Player1Yellow_type2,
            Player1Yellow_type3,
            Player1Yellow_type4,

            Player2Green_type1,
            Player2Green_type2,
            Player2Green_type3,
            Player2Green_type4,

            EnemyWhite_type1,
            EnemyWhite_type2,
            EnemyWhite_type3,
            EnemyWhite_type4,

            EnemyGreen_type1,
            EnemyGreen_type2,
            EnemyGreen_type3,
            EnemyGreen_type4,

            EnemyRed_type1,
            EnemyRed_type2,
            EnemyRed_type3,
            EnemyRed_type4
        };
         inline static std::string TankTypeToSpriteString[] = {
            "player1_yellow_tank_type1_sprite",
            "player1_yellow_tank_type2_sprite",
            "player1_yellow_tank_type3_sprite",
            "player1_yellow_tank_type4_sprite",

            "player2_green_tank_type1_sprite",
            "player2_green_tank_type2_sprite",
            "player2_green_tank_type3_sprite",
            "player2_green_tank_type4_sprite",

            "enemy_white_tank_type1_sprite",
            "enemy_white_tank_type2_sprite",
            "enemy_white_tank_type3_sprite",
            "enemy_white_tank_type4_sprite",

            "enemy_green_tank_type1_sprite",
            "enemy_green_tank_type2_sprite",
            "enemy_green_tank_type3_sprite",
            "enemy_green_tank_type4_sprite",

            "enemy_red_tank_type1_sprite",
            "enemy_red_tank_type2_sprite",
            "enemy_red_tank_type3_sprite",
            "enemy_red_tank_type4_sprite"
        };
    private:
        Orienation                          orient_;

        std::shared_ptr< renderer::Sprite > spriteTop_;
        std::shared_ptr< renderer::Sprite > spriteBottom_;
        std::shared_ptr< renderer::Sprite > spriteLeft_;
        std::shared_ptr< renderer::Sprite > spriteRight_;
        
        float                               maxAllowedSpd_;

        renderer::SpriteAnimator            animatorTop_;
        renderer::SpriteAnimator            animatorBottom_;
        renderer::SpriteAnimator            animatorLeft_;
        renderer::SpriteAnimator            animatorRight_;


        SpritePtr                           spriteRespawn_;
        renderer::SpriteAnimator            respawnAnimator_;
        bool                                isSpawning_{ true };

        SpritePtr                           spriteShield_;
        renderer::SpriteAnimator            shieldAnimator_;
        bool                                hasShield_{ false };

        sys::Timer                          respawnTimer_;
        sys::Timer                          shieldTimer_;

        std::shared_ptr< Bullet >           bulletPtr_;

        std::unique_ptr< AIComponent >      aiPtr_;
    public:// == CTORs ==
        explicit Tank( ETankType type
        , bool hasAI
        , bool hasShield
        , Orienation orient
        , float spd
        , glm::vec2 const& pos
        , glm::vec2 const& zize
        , float layer );

    public:// == RenderObjectInterface ==
        virtual void render()const override;
        virtual void update( double deltaT ) override;
        virtual void setVelocity( float v ) override;
    public:// == Tank ==
        void setOrient( Orienation orient );
        
        float getMaxAllowedSpd()const{
            return maxAllowedSpd_;
        }

        void fire();

        static const std::string& getTankSpriteFromType(const ETankType eType);
    };
}