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
        
        using LevelDescription = std::vector< std::string >;
        using Levels = std::vector< LevelDescription >;

    private:// == MEMBERs ==
        std::string         exePath_;
        Programs            programs_;
        TextureMap          textures_;
        Sprites             sprites_;
        Levels              levels_;
        LevelDescription    startScreen_;
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
            , std::string const& initialSubTexName = "default" );

        SpritePtr getSprite( std::string const& name );

        TexturePtr loadTextureAtlas( std::string const& textureName
            , std::string const& path
            , unsigned subWidth
            , unsigned subHeight
            , std::vector<std::string> const& subNames
        );

        bool loadJSONResources( std::string const& path );

        Levels const& getLevels()const{
            return levels_;
        }

        LevelDescription const& getStartScreen()const{
            return startScreen_;
        }
    private:
        std::string getFileString( std::string const& fpath );
    };
} 