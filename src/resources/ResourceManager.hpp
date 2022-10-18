#pragma once

// std
#include <string>
#include <unordered_map>
#include <memory>

namespace renderer{
    class ShaderProgram;
    class Texture2D;
}

namespace resources{
    class ResourceManager{
    public:// == TYPEs ==
        using ProgramPtr = std::shared_ptr< renderer::ShaderProgram >;
        using Programs = std::unordered_map< std::string, ProgramPtr >;
        using TexturePtr = std::shared_ptr< renderer::Texture2D >;
        using TextureMap = std::unordered_map< std::string, TexturePtr >;

    private:// == MEMBERs ==
        std::string exePath_;
        Programs    programs_;
        TextureMap  textures_;

    public:// == ctor ==
        explicit ResourceManager( std::string const& exePath );
        ResourceManager( ResourceManager const& ) = delete;
        ResourceManager& operator =( ResourceManager const& ) = delete;
        ~ResourceManager() = default;

    public:// == ResourceManager ==
        ProgramPtr loadShaders( std::string const& shaderName, std::string const& vertexPath, std::string const& fragPath  );
        ProgramPtr getShaderProgram( std::string const& name );
    public:
        TexturePtr loadTexture( std::string const& texttureName, std::string const& path );
        TexturePtr getTexture( std::string const& texttureName );

    private:
        std::string getFileString( std::string const& fpath );
    };
}