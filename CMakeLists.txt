cmake_minimum_required(VERSION 3.20)

project(STM32RCT6 LANGUAGES C ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(STM32RCT6.elf
    Core/Src/main.c
    Core/Src/stm32f1xx_hal_msp.c
    Core/Src/stm32f1xx_hal_timebase_tim.c
    Core/Src/stm32f1xx_it.c
    Core/Src/syscalls.c
    Core/Src/sysmem.c
    Core/Src/system_stm32f1xx.c
    Core/Startup/startup_stm32f103rctx.s
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
    Freertos/Src/croutine.c
    Freertos/Src/heap_4.c
    Freertos/Src/list.c
    Freertos/Src/port.c
    Freertos/Src/queue.c
    Freertos/Src/stream_buffer.c
    Freertos/Src/tasks.c
    Freertos/Src/timers.c
    User/task/key_task.c
    Drivers/key.c
    User/keys/key_down.c
    User/keys/key_up.c
    User/keys/key1.c
    User/keys/key2.c
    User/keys/key3.c
    User/keys/key4.c


)

target_compile_features(STM32RCT6.elf PRIVATE c_std_11)

target_compile_definitions(STM32RCT6.elf PRIVATE
    USE_HAL_DRIVER
    STM32F103xE
)

target_include_directories(STM32RCT6.elf PRIVATE
    Core/Inc
    Drivers/STM32F1xx_HAL_Driver/Inc
    Drivers/STM32F1xx_HAL_Driver/Inc/Legacy
    Drivers/CMSIS/Device/ST/STM32F1xx/Include
    Drivers/CMSIS/Include
    Freertos/Inc
    User/task
    Drivers
    User/keys
)

target_compile_options(STM32RCT6.elf PRIVATE
    -mcpu=cortex-m3
    -mthumb
    -mfloat-abi=soft
    -ffunction-sections
    -fdata-sections
    -Wall
    -Wextra
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(STM32RCT6.elf PRIVATE DEBUG)
    target_compile_options(STM32RCT6.elf PRIVATE -Og -g3)
else()
    target_compile_options(STM32RCT6.elf PRIVATE -Os -g0)
endif()

target_link_options(STM32RCT6.elf PRIVATE
    -mcpu=cortex-m3
    -mthumb
    -mfloat-abi=soft
    -T${CMAKE_CURRENT_SOURCE_DIR}/STM32F103RCTX_FLASH.ld
    -Wl,--gc-sections
    -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/STM32RCT6.map
)

add_custom_command(TARGET STM32RCT6.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:STM32RCT6.elf> $<TARGET_FILE_DIR:STM32RCT6.elf>/STM32RCT6.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:STM32RCT6.elf> $<TARGET_FILE_DIR:STM32RCT6.elf>/STM32RCT6.bin
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:STM32RCT6.elf>
)
