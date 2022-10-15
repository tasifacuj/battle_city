#include "ResourceManager.hpp"
#include "../renderer/ShaderProgram.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

namespace resources{

ResourceManager::ResourceManager( std::string const& exePath )
: exePath_( exePath ){
    auto pos = exePath.find_last_of( "\\" );

    if( pos != std::string::npos ){
        exePath_ = exePath.substr( 0, pos );
    }
}

std::string ResourceManager::getFileString( std::string const& relative_fpath ){
    std::ifstream f( exePath_ + "/" + relative_fpath );

    if( !f.is_open() ){
        std::cout << "Cannot open " << relative_fpath << std::endl;
        return "";
    }

    std::stringstream strm;
    strm << f.rdbuf();
    return strm.str();
}

ResourceManager::ProgramPtr ResourceManager::loadShaders( std::string const& shaderName, std::string const& vertexPath, std::string const& fragPath  ){
    std::string vertexData = getFileString( vertexPath );

    if( vertexData.empty() ){
        std::cout << "cant load " << vertexPath << std::endl;
        return {};
    }

    std::string fragData = getFileString( fragPath );

    if( fragData.empty() ){
        std::cout << "cant load " << fragPath << std::endl;
        return {};
    }

    auto shaderProgPtr = std::make_shared< renderer::ShaderProgram >( vertexData, fragData );

    if( shaderProgPtr->isCompiled() ){
        programs_.emplace( shaderName, shaderProgPtr );
        return shaderProgPtr;
    }else{
        return {};
    }
}

ResourceManager::ProgramPtr ResourceManager::getShaderProgram( std::string const& name ){
    if( programs_.count( name ) ){
        return programs_[ name ];
    }else{
        std::cout << "Shader program " << name << "does not exist" << std::endl;
        return {};
    }
}

}// namespace resources