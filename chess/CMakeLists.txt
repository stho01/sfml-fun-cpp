file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(chess ${SOURCES})

find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Network)
find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries(chess PRIVATE SFML::Graphics SFML::Audio SFML::Network extensions nlohmann_json::nlohmann_json)

copy_assets_for(chess
    ${CMAKE_SOURCE_DIR}/chess/assets
    ${CMAKE_SOURCE_DIR}/extensions/assets/extensions
)  