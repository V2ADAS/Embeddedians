################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c \
../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c 

OBJS += \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.o \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.o \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.o \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.o \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.o \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.o \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.o \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.o \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.o \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.o \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.o \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.o \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.o \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.o \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.o 

C_DEPS += \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.d \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.d \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.d \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.d \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.d \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.d \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.d \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.d \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.d \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.d \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.d \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.d \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.d \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.d \
./Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.o: ../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.o: ../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.o: ../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.o: ../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.o: ../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.o: ../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.o: ../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.o: ../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.o: ../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.o: ../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.o: ../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.o: ../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.o: ../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.o: ../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.o: ../Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

