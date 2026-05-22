cmake_minimum_required(VERSION 3.10)
project(ai_image_forensics_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
find_package(OpenMP REQUIRED)

include_directories(include)

add_executable(forensics_engine
    src/main.cpp
    src/BasicStats.cpp
    src/EdgeAnalysis.cpp
)

target_link_libraries(forensics_engine
    ${OpenCV_LIBS}
    OpenMP::OpenMP_CXX
)