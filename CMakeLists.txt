cmake_minimum_required(VERSION 3.16)

project(weather-app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Qml Network Core)

qt_standard_project_setup()

add_subdirectory(backend)

qt_add_executable(weather-app
    main.cpp
)

qt_add_qml_module(weather-app
    RESOURCE_PREFIX ":/qt/qml/"
    URI weather-app
    VERSION 1.0
    QML_FILES
        Main.qml
)

target_link_libraries(weather-app
    PRIVATE
    Qt6::Quick
    Qt6::Qml
    weather
)

include(GNUInstallDirs)
install(TARGETS weather-app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/icons" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME})
