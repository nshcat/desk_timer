cmake_minimum_required(VERSION 3.16)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/stm32_gcc.cmake)

project(desk_timer C CXX ASM)

stm32_fetch_cmsis(G0)
stm32_fetch_hal(G0)

find_package(CMSIS COMPONENTS STM32G030F6 REQUIRED)
find_package(HAL COMPONENTS STM32G0 REQUIRED)

# This sets -g3 for debug builds, which includes DWARF GDB macros for memory mapped registers
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3")

# Enable support for C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE PROJECT_SOURCES_C ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE PROJECT_SOURCES_CXX ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx)

add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCES_C} ${PROJECT_SOURCES_CXX})
target_link_libraries(${CMAKE_PROJECT_NAME}
        CMSIS::STM32::G030F6
        STM32::NoSys
        HAL::STM32::G0::RCC
        HAL::STM32::G0::GPIO
        HAL::STM32::G0::CORTEX
        HAL::STM32::G0::SPI
        HAL::STM32::G0::PWREx
)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/sys)
stm32_print_size_of_target(${CMAKE_PROJECT_NAME})

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.bin
)

