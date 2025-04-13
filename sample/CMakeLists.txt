file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(sample ${SOURCES})

find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Network)

target_link_libraries(sample PRIVATE SFML::Graphics SFML::Audio SFML::Network extensions)

copy_assets_for(sample
    ${CMAKE_SOURCE_DIR}/sample/assets
    ${CMAKE_SOURCE_DIR}/extensions/assets/extensions
)