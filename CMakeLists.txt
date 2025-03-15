cmake_minimum_required(VERSION 3.28)
project(SolaKF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og -g")

add_library(SolaKFlib
        utils.cpp
        IMU.cpp
        unitTests.cpp
        CAM.cpp
        KF.cpp
        RWSW.cpp
        PPC.cpp
        SYSCMD.cpp
)

add_executable(SolaKF main.cpp)

target_link_libraries(SolaKF SolaKFlib)