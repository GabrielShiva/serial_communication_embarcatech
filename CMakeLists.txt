# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(serial_communication_project C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(serial_communication_project src/main.c src/ssd1306.c)

# Then generate PIO header
pico_generate_pio_header(serial_communication_project ${CMAKE_CURRENT_LIST_DIR}/ws2812b.pio)

pico_set_program_name(serial_communication_project "serial_communication_project")
pico_set_program_version(serial_communication_project "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(serial_communication_project 1)
pico_enable_stdio_usb(serial_communication_project 1)

# Add the standard library to the build
target_link_libraries(serial_communication_project
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(serial_communication_project PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(serial_communication_project 
        hardware_i2c
        hardware_uart
        hardware_pio
        hardware_clocks
        hardware_irq
        )

pico_add_extra_outputs(serial_communication_project)

