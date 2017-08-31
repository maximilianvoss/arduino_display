cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arduino-cmake/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME arduino_display)
project(${PROJECT_NAME})

set(CMAKE_VERBOSE_MAKEFILE on)

set(${PROJECT_NAME}_SRCS display.c StreamBridge.cpp streamwrapper.cpp)
set(${PROJECT_NAME}_HDRS display.h StreamBridge.h streamwrapper.h)

set(${PROJECT_NAME}_BOARD yun)
set(${PROJECT_NAME}_PORT /dev/cu.usbmodem1421)
set(${PROJECT_NAME}_PROGRAMMER avrispmkii)
set(ARDLIBS Bridge) 

generate_arduino_library(${PROJECT_NAME})
