cmake_minimum_required(VERSION 2.8.4)
#set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME arduino_display)
project(${PROJECT_NAME})

#set(CMAKE_VERBOSE_MAKEFILE on)

#add_subdirectory(display)
#add_subdirectory(wrapper)


set(${CMAKE_PROJECT_NAME}_SRCS arduino_gamingplatform.cpp StreamBridge.cpp StreamBridge.hpp)

set(${CMAKE_PROJECT_NAME}_BOARD yun)
set(${CMAKE_PROJECT_NAME}_PORT /dev/cu.usbmodem1421)
set(${CMAKE_PROJECT_NAME}_PROGRAMMER avrispmkii)
set(${CMAKE_PROJECT_NAME}_LIBS display)
set(ARDLIBS Bridge)

#print_board_list()
generate_arduino_firmware(${CMAKE_PROJECT_NAME})
