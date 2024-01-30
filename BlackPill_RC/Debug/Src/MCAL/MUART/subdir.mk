################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/MUART/MUSART_Program.c 

OBJS += \
./Src/MCAL/MUART/MUSART_Program.o 

C_DEPS += \
./Src/MCAL/MUART/MUSART_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/MUART/%.o Src/MCAL/MUART/%.su Src/MCAL/MUART/%.cyclo: ../Src/MCAL/MUART/%.c Src/MCAL/MUART/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-MUART

clean-Src-2f-MCAL-2f-MUART:
	-$(RM) ./Src/MCAL/MUART/MUSART_Program.cyclo ./Src/MCAL/MUART/MUSART_Program.d ./Src/MCAL/MUART/MUSART_Program.o ./Src/MCAL/MUART/MUSART_Program.su

.PHONY: clean-Src-2f-MCAL-2f-MUART

