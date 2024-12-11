cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

set(PROJECT_NAME "pico-snes-controller")

project(${PROJECT_NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(${PROJECT_NAME}
    main.c
    snes_controller.c
)

pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/snes_controller.pio)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_pio
)

pico_enable_stdio_uart(${PROJECT_NAME} 1)
pico_enable_stdio_usb(${PROJECT_NAME} 1)

pico_add_extra_outputs(${PROJECT_NAME})
