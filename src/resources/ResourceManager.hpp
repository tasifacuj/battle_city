#pragma once

// std
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

// rj
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"

namespace renderer{
    class ShaderProgram;
    class Texture2D;
    class Sprite;
    class AnimatedSprite;
}

namespace resources{
    class ResourceManager{
    public:// == TYPEs ==
        using ProgramPtr = std::shared_ptr< renderer::ShaderProgram >;
        using Programs = std::unordered_map< std::string, ProgramPtr >;
        using TexturePtr = std::shared_ptr< renderer::Texture2D >;
        using TextureMap = std::unordered_map< std::string, TexturePtr >;
        using SpritePtr = std::shared_ptr< renderer::Sprite >;
        using Sprites = std::unordered_map< std::string, SpritePtr >;
        using AnimatedSpritePtr = std::shared_ptr<renderer::AnimatedSprite>;
        using AnimatedSprites = std::unordered_map< std::string, AnimatedSpritePtr >;

    private:// == MEMBERs ==
        std::string     exePath_;
        Programs        programs_;
        TextureMap      textures_;
        Sprites         sprites_;
        AnimatedSprites animatedSprites_;
    public:// == ctor ==
        ResourceManager() = default;
        ResourceManager( ResourceManager const& ) = delete;
        ResourceManager& operator =( ResourceManager const& ) = delete;
        ~ResourceManager() = default;
    public:
        static ResourceManager& getInstance();

    public:// == ResourceManager ==
        void initialize( std::string const& exePath );
        void free();
    
        ProgramPtr loadShaders( std::string const& shaderName, std::string const& vertexPath, std::string const& fragPath  );
        ProgramPtr getShaderProgram( std::string const& name );
    
        TexturePtr loadTexture( std::string const& texttureName, std::string const& path );
        TexturePtr getTexture( std::string const& texttureName );

        SpritePtr loadSprite( std::string const& name
            , std::string const& textureName
            , std::string const& programName
            , unsigned width
            , unsigned height
            , std::string const& initialSubTexName = "default" );

        SpritePtr getSprite( std::string const& name );

        AnimatedSpritePtr loadAnimatedSprite( std::string const& name
            , std::string const& textureName
            , std::string const& programName
            , unsigned width
            , unsigned height
            , std::string const& initialSubTexName = "default" 
        );

        AnimatedSpritePtr getAnimatedSprite( std::string const& name );

        TexturePtr loadTextureAtlas( std::string const& textureName
            , std::string const& path
            , unsigned subWidth
            , unsigned subHeight
            , std::vector<std::string> const& subNames
        );

        bool loadJSONResources( std::string const& path );
    private:
        std::string getFileString( std::string const& fpath );
    };
} 