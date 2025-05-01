file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(fireworks ${SOURCES})

find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Network)

target_link_libraries(fireworks PRIVATE SFML::Graphics SFML::Audio SFML::Network extensions)

copy_assets_for(fireworks
    ${CMAKE_SOURCE_DIR}/fireworks/assets
    ${CMAKE_SOURCE_DIR}/extensions/assets/extensions
)