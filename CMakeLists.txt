cmake_minimum_required(VERSION 3.16)

project(machine_monitoring_hmi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2)

add_executable(machine_monitoring_hmi
    src/main.cpp
    src/TelemetryModel.cpp
    include/TelemetryModel.hpp
)

target_include_directories(machine_monitoring_hmi PRIVATE include)

target_compile_definitions(machine_monitoring_hmi
    PRIVATE APP_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(machine_monitoring_hmi
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
)
