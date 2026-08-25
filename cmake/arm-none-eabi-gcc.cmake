set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(ARM_TOOLCHAIN_DIR "C:/Users/28970/Toolchain/ArmGNU/bin" CACHE PATH "Directory containing arm-none-eabi toolchain executables")

if(ARM_TOOLCHAIN_DIR)
    set(CMAKE_C_COMPILER "${ARM_TOOLCHAIN_DIR}/arm-none-eabi-gcc.exe")
    set(CMAKE_ASM_COMPILER "${ARM_TOOLCHAIN_DIR}/arm-none-eabi-gcc.exe")
    set(CMAKE_OBJCOPY "${ARM_TOOLCHAIN_DIR}/arm-none-eabi-objcopy.exe")
    set(CMAKE_SIZE "${ARM_TOOLCHAIN_DIR}/arm-none-eabi-size.exe")
else()
    find_program(CMAKE_C_COMPILER arm-none-eabi-gcc REQUIRED)
    set(CMAKE_ASM_COMPILER "${CMAKE_C_COMPILER}")
    find_program(CMAKE_OBJCOPY arm-none-eabi-objcopy REQUIRED)
    find_program(CMAKE_SIZE arm-none-eabi-size REQUIRED)
endif()

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
