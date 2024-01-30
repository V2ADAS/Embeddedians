################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/MGPIO/MGPIO_Prog.c 

OBJS += \
./Src/MCAL/MGPIO/MGPIO_Prog.o 

C_DEPS += \
./Src/MCAL/MGPIO/MGPIO_Prog.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/MGPIO/%.o Src/MCAL/MGPIO/%.su Src/MCAL/MGPIO/%.cyclo: ../Src/MCAL/MGPIO/%.c Src/MCAL/MGPIO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-MGPIO

clean-Src-2f-MCAL-2f-MGPIO:
	-$(RM) ./Src/MCAL/MGPIO/MGPIO_Prog.cyclo ./Src/MCAL/MGPIO/MGPIO_Prog.d ./Src/MCAL/MGPIO/MGPIO_Prog.o ./Src/MCAL/MGPIO/MGPIO_Prog.su

.PHONY: clean-Src-2f-MCAL-2f-MGPIO

