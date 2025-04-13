add_library(extensions STATIC
    src/GameBase.cpp
    src/Timer.cpp
    src/WindowFactory.cpp
    src/FloatCircle.cpp
    src/FloatLine.cpp
    src/Mathf.cpp
    src/GameFpsRenderer.cpp
    src/Logger.cpp
)

target_include_directories(extensions PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Network)

target_link_libraries(extensions PRIVATE SFML::Graphics SFML::Audio SFML::Network)