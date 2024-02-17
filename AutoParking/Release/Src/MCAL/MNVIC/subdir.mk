################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/MNVIC/MNVIC_Prog.c 

OBJS += \
./Src/MCAL/MNVIC/MNVIC_Prog.o 

C_DEPS += \
./Src/MCAL/MNVIC/MNVIC_Prog.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/MNVIC/MNVIC_Prog.o: ../Src/MCAL/MNVIC/MNVIC_Prog.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/MCAL/MNVIC/MNVIC_Prog.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

