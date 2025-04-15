file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(quadtree ${SOURCES})

find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Network)

target_link_libraries(quadtree PRIVATE SFML::Graphics SFML::Audio SFML::Network extensions)

copy_assets_for(quadtree
    ${CMAKE_SOURCE_DIR}/extensions/assets/extensions
)