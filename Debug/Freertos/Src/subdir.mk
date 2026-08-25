################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Freertos/Src/croutine.c \
../Freertos/Src/heap_4.c \
../Freertos/Src/list.c \
../Freertos/Src/port.c \
../Freertos/Src/queue.c \
../Freertos/Src/stream_buffer.c \
../Freertos/Src/tasks.c \
../Freertos/Src/timers.c 

OBJS += \
./Freertos/Src/croutine.o \
./Freertos/Src/heap_4.o \
./Freertos/Src/list.o \
./Freertos/Src/port.o \
./Freertos/Src/queue.o \
./Freertos/Src/stream_buffer.o \
./Freertos/Src/tasks.o \
./Freertos/Src/timers.o 

C_DEPS += \
./Freertos/Src/croutine.d \
./Freertos/Src/heap_4.d \
./Freertos/Src/list.d \
./Freertos/Src/port.d \
./Freertos/Src/queue.d \
./Freertos/Src/stream_buffer.d \
./Freertos/Src/tasks.d \
./Freertos/Src/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Freertos/Src/%.o Freertos/Src/%.su Freertos/Src/%.cyclo: ../Freertos/Src/%.c Freertos/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"E:/Users/28970/STM32/Freertos_learn/example2.4/Freertos/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Freertos-2f-Src

clean-Freertos-2f-Src:
	-$(RM) ./Freertos/Src/croutine.cyclo ./Freertos/Src/croutine.d ./Freertos/Src/croutine.o ./Freertos/Src/croutine.su ./Freertos/Src/heap_4.cyclo ./Freertos/Src/heap_4.d ./Freertos/Src/heap_4.o ./Freertos/Src/heap_4.su ./Freertos/Src/list.cyclo ./Freertos/Src/list.d ./Freertos/Src/list.o ./Freertos/Src/list.su ./Freertos/Src/port.cyclo ./Freertos/Src/port.d ./Freertos/Src/port.o ./Freertos/Src/port.su ./Freertos/Src/queue.cyclo ./Freertos/Src/queue.d ./Freertos/Src/queue.o ./Freertos/Src/queue.su ./Freertos/Src/stream_buffer.cyclo ./Freertos/Src/stream_buffer.d ./Freertos/Src/stream_buffer.o ./Freertos/Src/stream_buffer.su ./Freertos/Src/tasks.cyclo ./Freertos/Src/tasks.d ./Freertos/Src/tasks.o ./Freertos/Src/tasks.su ./Freertos/Src/timers.cyclo ./Freertos/Src/timers.d ./Freertos/Src/timers.o ./Freertos/Src/timers.su

.PHONY: clean-Freertos-2f-Src

