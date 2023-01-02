cmake_minimum_required(VERSION 3.16)

project(TicTacToe VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

add_executable(TicTacToe
    main.cpp
    application.h
    application.cpp
    application.ui
    Options.cpp
    Options.h
    Options.ui
    resources.qrc
    game.h
    game.cpp
    game.ui
    gameplay.h
    gameplay.cpp
)


target_link_libraries(TicTacToe PRIVATE Qt6::Widgets)
target_link_libraries(TicTacToe PRIVATE Qt6::Network)

set_target_properties(TicTacToe PROPERTIES
    MACOSX_BUNDLE ON
    WIN32_EXECUTABLE ON
)
