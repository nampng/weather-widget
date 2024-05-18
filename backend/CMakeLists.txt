cmake_minimum_required(VERSION 3.16)

project(backend VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(../keys)

qt_add_library(backend STATIC
    weather.cpp
    weather.h
)

target_link_libraries(backend
    PRIVATE
    Qt6::Quick
    Qt6::Qml
    Qt6::Network
    Qt6::Core
)

target_include_directories(backend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/weather_conditions.json" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
