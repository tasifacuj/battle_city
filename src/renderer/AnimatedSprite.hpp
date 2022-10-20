#pragma once

// project
#include "Sprite.hpp"

// std
#include <map>
#include <vector>

namespace renderer{
    class AnimatedSprite : public Sprite{
    public:// == TYPES ==
        // subtexture_name --> duration
        using Frame     = std::pair< std::string, size_t >;
        using FrameVec  = std::vector<Frame>;
        using StateMap = std::map< std::string, FrameVec >;
        using ConstIterator = StateMap::const_iterator;
    private: // == MEMBERS ==
        StateMap        stateMap_;
        size_t          frame_{0};
        size_t          animationTimeMS_{0};//!< how much time passed from the moment when we started particular frame
        ConstIterator   animationDurationIt_;
        bool            dirty_{ false };
    public:// == CTORs ==
        AnimatedSprite( std::shared_ptr< Texture2D > texPtr
            , std::string const& initialSubTexName
            , std::shared_ptr< ShaderProgram > programPtr
            , glm::vec2 const& pos = glm::vec2( 0.0f )
            , glm::vec2 const& size = glm::vec2( 1.0f )
            , float angle = 0.0f 
        );
    public:// == Sprite ==
        virtual void render() override;

    public:// == AnimatedSprite ==
        /**
         * @param state jump, go, drive
         * @param frames, list of 
        */
        void addState( std::string const& state, FrameVec const& frames ){
            stateMap_.emplace( state, frames );
        }

        void update( size_t deltaTMS );
        void setState( std::string const& newState );
    };
}//namespace renderer