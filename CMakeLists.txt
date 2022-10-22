cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
set( PROJECT_NAME BattleCity )
project(${PROJECT_NAME})

add_executable( BattleCity 
	src/main.cpp 

	src/renderer/ShaderProgram.cpp
	src/renderer/ShaderProgram.hpp
	src/renderer/Texture2D.cpp
	src/renderer/Texture2D.hpp
	src/renderer/Sprite.cpp
	src/renderer/Sprite.hpp
	src/renderer/AnimatedSprite.cpp
	src/renderer/AnimatedSprite.hpp
	src/renderer/VertexBufferObject.cpp
	src/renderer/VertexBufferObject.hpp
	src/renderer/IndexBufferObject.cpp
	src/renderer/IndexBufferObject.hpp
	src/renderer/VertexArrayObject.cpp
	src/renderer/VertexArrayObject.hpp
	src/renderer/VertexBufferLayout.cpp
	src/renderer/VertexBufferLayout.hpp
	src/renderer/Renderer.cpp
	src/renderer/Renderer.hpp

	src/resources/ResourceManager.cpp
	src/resources/ResourceManager.hpp
	src/resources/stb_image.h

	src/game/Game.cpp
	src/game/Game.hpp
	src/game/Tank.cpp
	src/game/Tank.hpp
)

target_compile_features( ${PROJECT_NAME} PUBLIC cxx_std_17 )

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory( external/glfw )
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory( external/glad )
target_link_libraries(${PROJECT_NAME} glad)

include_directories( external/glm )

set_target_properties( ${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )

add_custom_command( TARGET ${PROJECT_NAME} POST_BUILD
 	COMMAND ${CMAKE_COMMAND} -E copy_directory 
	${CMAKE_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/res )	