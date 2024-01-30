################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/MSPI/MSPI_Prog.c 

OBJS += \
./Src/MCAL/MSPI/MSPI_Prog.o 

C_DEPS += \
./Src/MCAL/MSPI/MSPI_Prog.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/MSPI/%.o Src/MCAL/MSPI/%.su Src/MCAL/MSPI/%.cyclo: ../Src/MCAL/MSPI/%.c Src/MCAL/MSPI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-MSPI

clean-Src-2f-MCAL-2f-MSPI:
	-$(RM) ./Src/MCAL/MSPI/MSPI_Prog.cyclo ./Src/MCAL/MSPI/MSPI_Prog.d ./Src/MCAL/MSPI/MSPI_Prog.o ./Src/MCAL/MSPI/MSPI_Prog.su

.PHONY: clean-Src-2f-MCAL-2f-MSPI

