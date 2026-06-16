cmake_minimum_required(VERSION 3.16)

project(machine_monitoring_hmi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Needed because we use Qt QObject, Q_OBJECT, signals, slots, Q_PROPERTY
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2)

# ROS2 dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(machine_interfaces REQUIRED)
find_package(std_srvs REQUIRED)

add_executable(machine_monitoring_hmi
    src/main.cpp
    src/TelemetryModel.cpp
    src/Ros2TelemetryClient.cpp
    src/Ros2CommandClient.cpp

    include/TelemetryModel.hpp
    include/Ros2TelemetryClient.hpp
    include/Ros2CommandClient.hpp
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

ament_target_dependencies(machine_monitoring_hmi
    rclcpp
    machine_interfaces
    std_srvs
)
