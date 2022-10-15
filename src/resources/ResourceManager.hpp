#pragma once

// std
#include <string>
#include <unordered_map>
#include <memory>

namespace renderer{
    class ShaderProgram;
}

namespace resources{
    class ResourceManager{
    public:// == TYPEs ==
        using ProgramPtr = std::shared_ptr< renderer::ShaderProgram >;
        using Programs = std::unordered_map< std::string, ProgramPtr >;
    private:
        std::string exePath_;
        Programs programs_;
        
    public:// == ctor ==
        explicit ResourceManager( std::string const& exePath );
        ResourceManager( ResourceManager const& ) = delete;
        ResourceManager& operator =( ResourceManager const& ) = delete;
        ~ResourceManager() = default;

    public:
        ProgramPtr loadShaders( std::string const& shaderName, std::string const& vertexPath, std::string const& fragPath  );
        ProgramPtr getShaderProgram( std::string const& name );

    private:
        std::string getFileString( std::string const& fpath );
    };
}