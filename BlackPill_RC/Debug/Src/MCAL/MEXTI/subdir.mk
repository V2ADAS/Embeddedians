################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/MEXTI/MEXTI_Prog.c 

OBJS += \
./Src/MCAL/MEXTI/MEXTI_Prog.o 

C_DEPS += \
./Src/MCAL/MEXTI/MEXTI_Prog.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/MEXTI/%.o Src/MCAL/MEXTI/%.su Src/MCAL/MEXTI/%.cyclo: ../Src/MCAL/MEXTI/%.c Src/MCAL/MEXTI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-MEXTI

clean-Src-2f-MCAL-2f-MEXTI:
	-$(RM) ./Src/MCAL/MEXTI/MEXTI_Prog.cyclo ./Src/MCAL/MEXTI/MEXTI_Prog.d ./Src/MCAL/MEXTI/MEXTI_Prog.o ./Src/MCAL/MEXTI/MEXTI_Prog.su

.PHONY: clean-Src-2f-MCAL-2f-MEXTI

