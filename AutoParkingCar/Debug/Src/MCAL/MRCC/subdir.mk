################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/MRCC/MRCC_Prog.c 

OBJS += \
./Src/MCAL/MRCC/MRCC_Prog.o 

C_DEPS += \
./Src/MCAL/MRCC/MRCC_Prog.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/MRCC/MRCC_Prog.o: ../Src/MCAL/MRCC/MRCC_Prog.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F401RCTx -DDEBUG -c -I../Inc -I../Inc/STM32F4xx_HAL_Driver/Inc/Legacy -I../Inc/STM32F4xx_HAL_Driver/Inc -I../Inc/CMSIS/Device/ST/STM32F4xx/Include -I../Inc/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -fstack-usage -MMD -MP -MF"Src/MCAL/MRCC/MRCC_Prog.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

