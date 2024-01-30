################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/HSERVO/HSERVO_Prog.c 

OBJS += \
./Src/HAL/HSERVO/HSERVO_Prog.o 

C_DEPS += \
./Src/HAL/HSERVO/HSERVO_Prog.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/HSERVO/%.o Src/HAL/HSERVO/%.su Src/HAL/HSERVO/%.cyclo: ../Src/HAL/HSERVO/%.c Src/HAL/HSERVO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-HSERVO

clean-Src-2f-HAL-2f-HSERVO:
	-$(RM) ./Src/HAL/HSERVO/HSERVO_Prog.cyclo ./Src/HAL/HSERVO/HSERVO_Prog.d ./Src/HAL/HSERVO/HSERVO_Prog.o ./Src/HAL/HSERVO/HSERVO_Prog.su

.PHONY: clean-Src-2f-HAL-2f-HSERVO

