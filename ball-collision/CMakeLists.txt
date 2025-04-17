file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(ballcollision ${SOURCES})

find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Network)

target_link_libraries(ballcollision PRIVATE SFML::Graphics SFML::Audio SFML::Network extensions)

copy_assets_for(ballcollision
    ${CMAKE_SOURCE_DIR}/extensions/assets/extensions
)  