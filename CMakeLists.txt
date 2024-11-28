cmake_minimum_required(VERSION 3.31)

# Modify these settings for your application
set(ProjectName "GamePhysicsEngine2D")
list(APPEND ProjectSources ${ProjectName}.cpp 
    source/physics/Body.cpp
    source/physics/CollisionDetection.cpp
    source/physics/IShape.cpp
    source/physics/shapes/ShapeBox.cpp
    source/physics/shapes/ShapePolygon.cpp
    source/physics/shapes/ShapeCircle.cpp
    )

# Common settings for all applications
project(${ProjectName})
list(APPEND ProjectSources main.cpp source/Application.cpp source/Colour.cpp source/Renderer.cpp source/Vector2.cpp)
add_executable(${ProjectName} ${ProjectSources})
set_property(TARGET ${ProjectName} PROPERTY CXX_STANDARD 20)
target_include_directories(${ProjectName} PUBLIC /opt/homebrew/include/ source)
target_link_directories(${ProjectName} PUBLIC /opt/homebrew/lib/)
target_link_libraries(${ProjectName} SDL2 SDL2_gfx)
