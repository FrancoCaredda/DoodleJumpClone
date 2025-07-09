cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 17)

project("Game")
add_executable(${PROJECT_NAME} "src/main.cpp" "src/Game.h" "src/Game.cpp" "src/Sprites.h" "src/Sprites.cpp" "src/Entity.h" "src/Renderer.h" "src/Renderer.cpp"     "src/World.h" "src/World.cpp")
add_compile_definitions(SOURCE_DIR="${CMAKE_SOURCE_DIR}")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/Lib/RayLib/include")
target_link_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/Lib/RayLib/lib")
target_link_libraries(${PROJECT_NAME} "raylib.lib" "winmm.lib")