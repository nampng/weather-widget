cmake_minimum_required(VERSION 3.16)

project(weather-widget VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Qml Network Core)

qt_standard_project_setup()

add_subdirectory(backend)

qt_add_executable(weather-widget
    main.cpp
)

qt_add_qml_module(weather-widget
    VERSION 1.0
    URI weather-widget
    QML_FILES
        Main.qml
)

target_link_libraries(weather-widget
    PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Qml
    backend
)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/icons" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME})
