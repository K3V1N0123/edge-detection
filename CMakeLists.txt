cmake_minimum_required(VERSION 3.18)

project(edge_detection LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(EDGE_DETECTION_ENABLE_OPENCV "Enable OpenCV-dependent targets" ON)
option(EDGE_DETECTION_ENABLE_CUDA "Enable CUDA targets when toolchain is available" OFF)

add_library(project_warnings INTERFACE)
target_compile_options(project_warnings INTERFACE
    $<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

add_library(edge_common
    src/common/timer.cpp
)

target_include_directories(edge_common PUBLIC include)
target_link_libraries(edge_common PUBLIC project_warnings)

add_executable(cpu_baseline
    src/cpu/main.cpp
)

target_link_libraries(cpu_baseline PRIVATE edge_common)
target_include_directories(cpu_baseline PRIVATE include)

if(EDGE_DETECTION_ENABLE_OPENCV)
    find_package(OpenCV QUIET)
    if(OpenCV_FOUND)
        target_compile_definitions(cpu_baseline PRIVATE EDGE_DETECTION_HAS_OPENCV=1)
        target_link_libraries(cpu_baseline PRIVATE ${OpenCV_LIBS})
        target_include_directories(cpu_baseline PRIVATE ${OpenCV_INCLUDE_DIRS})
    else()
        message(WARNING "OpenCV not found. cpu_baseline will build in placeholder mode.")
    endif()
endif()

if(EDGE_DETECTION_ENABLE_CUDA)
    enable_language(CUDA)

    add_executable(cuda_stub
        src/cuda/naive_stub.cu
    )

    set_target_properties(cuda_stub PROPERTIES
        CUDA_STANDARD 14
        CUDA_STANDARD_REQUIRED ON
    )

    target_link_libraries(cuda_stub PRIVATE project_warnings)
    target_include_directories(cuda_stub PRIVATE include)
endif()
