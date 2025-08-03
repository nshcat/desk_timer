cmake_minimum_required(VERSION 3.16)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/stm32_gcc.cmake)

project(desk_timer C CXX ASM)

stm32_fetch_cmsis(G0)
stm32_fetch_hal(G0)

find_package(CMSIS COMPONENTS STM32G0B1CB REQUIRED)
find_package(HAL COMPONENTS STM32G0 REQUIRED)

# This sets -g3 for debug builds, which includes DWARF GDB macros for memory mapped registers
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -feliminate-unused-debug-symbols -fdata-sections -ffunction-sections")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -feliminate-unused-debug-symbols -fdata-sections -ffunction-sections")

# Disable RTTI
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-exceptions")

# Enable support for C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include third party dependencies
add_subdirectory(thirdparty/u8g2)

file(GLOB_RECURSE PROJECT_SOURCES_C ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE PROJECT_SOURCES_CXX ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx)

# Add main project executable
add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCES_C} ${PROJECT_SOURCES_CXX})

# Enable LTO
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

target_link_libraries(${CMAKE_PROJECT_NAME}
    # -- STM32 HAL libraries
    CMSIS::STM32::G0B1CB
    STM32::NoSys
    HAL::STM32::G0::RCC
    HAL::STM32::G0::RCCEx
    HAL::STM32::G0::RTC
    HAL::STM32::G0::RTCEx
    HAL::STM32::G0::GPIO
    HAL::STM32::G0::CORTEX
    HAL::STM32::G0::SPI
    HAL::STM32::G0::TIM
    HAL::STM32::G0::TIMEx
    HAL::STM32::G0::PWREx
    HAL::STM32::G0::UART
    HAL::STM32::G0::UARTEx
    HAL::STM32::G0::DMA

    # -- Thirdparty libraries
    u8g2
)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/sys)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/hal)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/u8g2)
stm32_generate_binary_file(${CMAKE_PROJECT_NAME})

# Show total flash and ram usage after build
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_SIZE} --format=sysv $<TARGET_FILE:${CMAKE_PROJECT_NAME}> | python ${CMAKE_CURRENT_SOURCE_DIR}/scripts/stats.py --mem-usage --color --newline --flash-size=131072 --ram-size=147456
)

# Custom target to show detailed memory usage per symbol
find_program(CMAKE_NM NAMES ${STM32_TARGET_TRIPLET}-nm HINTS ${TOOLCHAIN_BIN_PATH})
add_custom_target(symbol_summary
    COMMAND ${CMAKE_NM} $<TARGET_FILE:${CMAKE_PROJECT_NAME}> -S --radix=d --size-sort --reverse-sort --format=sysv | python ${CMAKE_CURRENT_SOURCE_DIR}/scripts/stats.py --sym-size
)

# Target that starts the openocd server for debugging via stlink
add_custom_target(openocd_server
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/debug/start_openocd.sh
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/debug
)

# Target that starts gdb connected to the openocd server
add_custom_target(gdb
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/debug/start_gdb.sh
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/debug
)

# Target that flashes the microcontroller via connected ST-LINKV2.1
add_custom_target(flash
    COMMAND st-flash write ${CMAKE_PROJECT_NAME}.bin 0x08000000
)
