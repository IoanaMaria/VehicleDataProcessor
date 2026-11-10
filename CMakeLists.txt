cmake_minimum_required(VERSION 3.21)

project(VehicleDataProcessor VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

add_executable(vehicle_data_processor
    app/main.cpp
    include/common/Message.h
    include/simulation/VehicleSimulator.h
    src/simulation/VehicleSimulator.cpp
    include/processing/VehicleDataProcessor.h
    src/processing/VehicleDataProcessor.cpp
)

target_include_directories(vehicle_data_processor PRIVATE include)
target_link_libraries(vehicle_data_processor PRIVATE Qt6::Core)
