#include "ResourceManager.hpp"
#include "../renderer/ShaderProgram.hpp"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"
#include "../renderer/Texture2D.hpp"
#include "../renderer/Sprite.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

namespace rj = rapidjson;

namespace resources{

ResourceManager& ResourceManager::getInstance(){
    static ResourceManager s_resMgr;
    return s_resMgr;
}

void ResourceManager::initialize( std::string const& exePath ){
    exePath_ =  exePath;
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
        std::cout << "Shader program " << name << " does not exist" << std::endl;
        return {};
    }
}

ResourceManager::TexturePtr ResourceManager::loadTexture( std::string const& textureName, std::string const& path ){
    int channels = 0;
    int width = 0;
    int height = 0;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* pixelData = stbi_load( ( exePath_ + "/" + path ).c_str(), &width, &height, &channels, 0 );

    if( !pixelData ){
        std::cout << "Cannot load " << path << std::endl;
        return {};
    }

    TexturePtr texPtr = std::make_shared< renderer::Texture2D >( width, height, pixelData, channels, GL_NEAREST, GL_CLAMP_TO_EDGE );
    textures_[ textureName ]  = texPtr;
    stbi_image_free( pixelData );
    return texPtr;
}

ResourceManager::TexturePtr ResourceManager::getTexture( std::string const& textureName ){
    if( textures_.count( textureName ) ){
        return textures_[ textureName ];
    }else{
        std::cout << "Cannot find texture " << textureName << std::endl;
        return {};
    }
}

ResourceManager::SpritePtr ResourceManager::loadSprite( std::string const& name, std::string const& textureName, std::string const& programName, std::string const& initialSubTexName ){
    auto texPtr = getTexture( textureName );

    if( !texPtr ){
        return {};
    }

    auto programPtr = getShaderProgram( programName );

    if( !programPtr ){
        return {};
    }

    auto spritePtr = std::make_shared< renderer::Sprite>( texPtr, initialSubTexName, programPtr );
    sprites_[ name ] = spritePtr;
    return spritePtr;
}

ResourceManager::SpritePtr ResourceManager::getSprite( std::string const& name ){
    if( sprites_.count( name ) ){
        return sprites_[ name ];
    }else{
        std::cout << "Cannot find sprite " << name << std::endl;
        return {};
    }
}

ResourceManager::TexturePtr ResourceManager::loadTextureAtlas( std::string const& textureName, std::string const& path, unsigned subWidth, unsigned subHeight, std::vector<std::string> const& subNames ){
    auto texPtr = loadTexture( textureName, path );

    if( !texPtr ){
        return {};
    }

    unsigned texWidth = texPtr->width();
    unsigned texHeight = texPtr->height();
    unsigned textureOffsetX = 0;
    unsigned textureOffsetY = texHeight;

    for( auto const& subName : subNames ){
        float u = static_cast<float>( textureOffsetX + 0.01f ) / texWidth;
        float v = static_cast<float>( textureOffsetY - subHeight + 0.01f ) / texHeight;
        glm::vec2 leftBottomUV( u, v );

        float u_rt = static_cast<float>( textureOffsetX + subWidth  - 0.01f ) / texWidth;
        float v_rt = static_cast<float>( textureOffsetY - 0.01f ) / texHeight;
        glm::vec2 rightTopUV( u_rt, v_rt );

        textureOffsetX += subWidth;

        if( textureOffsetX >= texWidth ){
            textureOffsetX = 0;
            textureOffsetY -= subHeight;
        }

        texPtr->addSubtexture( subName, leftBottomUV, rightTopUV );
    }

    return texPtr;
}



void ResourceManager::free(){
    sprites_.clear();
    textures_.clear();
    programs_.clear();
}

bool ResourceManager::loadJSONResources( std::string const& path ){
    std::string content = getFileString( path );

    if( content.empty() ){
        std::cout << path << " json is empty";
        return false;
    }

    rapidjson::Document document;
    rapidjson::ParseResult errval = document.Parse( content.c_str() );

    if( !errval ){
        std::cout << "file: " << path <<  ", JSON parse error: " << GetParseError_En( errval.Code() ) << ", offset: " << errval.Offset() << std::endl;
        return false;
    }

    {
        // 1. shaders
        auto shader_it = document.FindMember( "shaders" );

        if( shader_it != document.MemberEnd() ){
            rj::Value const& shVal = shader_it->value;

            for( rj::Value const& shader : shVal.GetArray() ){
                std::string name = shader["name"].GetString();
                std::string filePath_v = shader[ "filePath_v" ].GetString();
                std::string filePath_f = shader[ "filePath_f" ].GetString();
                loadShaders( name, filePath_v, filePath_f );
            }
        }
    }

    {
        // 2. texture atlases
        auto tex_it = document.FindMember( "textureAtlases" );

        if( tex_it != document.MemberEnd() ){
            rj::Value const& texVal = tex_it->value;

            for( rj::Value const& tex : texVal.GetArray() ){
                std::string name = tex["name"].GetString();
                std::string filePath = tex[ "filePath" ].GetString();
                unsigned subtextureWidth = tex[ "subtextureWidth" ].GetUint();
                unsigned subtextureHeight = tex[ "subtextureHeight" ].GetUint();
                std::vector< std::string > subnames;
                rj::Value const& subVal = tex["subtextureNames"];

                for( rj::Value const& subn : subVal.GetArray() ){
                    subnames.push_back( subn.GetString() );
                }

                loadTextureAtlas( name, filePath, subtextureWidth, subtextureHeight, subnames );
            }
        }
    }

    {// 4. map
        auto lev_it = document.FindMember( "levels" );

        if( lev_it != document.MemberEnd() ){
            rj::Value const& levelVal = lev_it->value;

            for( rj::Value const& lvl : levelVal.GetArray() ){
                rj::Value const& descriptionVal = lvl["description"];//array
                std::vector< std::string > rows;
                size_t maxLen = 0;

                for( rj::Value const& row : descriptionVal.GetArray() ){
                    rows.push_back( row.GetString() );

                    if( maxLen < rows.back().size() ){
                        maxLen = rows.back().size();
                    }
                }

                for( auto& row : rows ){
                    while( row.size() < maxLen ) row.append( 1, 'D' );
                }

                levels_.emplace_back( rows );
            }
        }
    }

    {// 5. ізкшеуі
        auto it = document.FindMember( "sprites" );

        if( it != document.MemberEnd() ){
            auto const& spritesVal = it->value;

            for( rj::Value const& spriteVal : spritesVal.GetArray() ){
                std::string name = spriteVal["name"].GetString();
                std::string texAtlas = spriteVal["textureAtlas"].GetString();
                std::string shader = spriteVal[ "shader" ].GetString();
                std::string subtexture = spriteVal["initialSubTexture"].GetString();
                auto spritePtr = loadSprite( name, texAtlas, shader, subtexture );

                if( !spritePtr ){
                    std::cout << "Failed to load " << name << " sprite\n";
                    continue;
                }

                auto framesIt = spriteVal.FindMember( "frames" );

                if( framesIt != spriteVal.MemberEnd() ){
                    auto const& framesArray = framesIt->value.GetArray();
                    std::vector< renderer::Sprite::FrameDescription > frames;

                    for( const rj::Value& f : framesArray ){
                        std::string subtextureName = f["subTexture"].GetString();
                        double duration = f[ "duration" ].GetDouble();
                        auto texAtlasPtr = getTexture( texAtlas );
                        auto subTexCoords = texAtlasPtr->getSubTex( subtextureName );
                        frames.emplace_back( renderer::Sprite::FrameDescription{ subTexCoords.leftBottomUV, subTexCoords.rightTopUV, duration } );
                    }

                    spritePtr->setFrames( std::forward< decltype( frames ) >( frames ) );
                }
            }
        }
    }

    return true;
}

}// namespace resources