################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/HCOMPASS/HAL_COMPASS.c 

OBJS += \
./Src/HAL/HCOMPASS/HAL_COMPASS.o 

C_DEPS += \
./Src/HAL/HCOMPASS/HAL_COMPASS.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/HCOMPASS/%.o Src/HAL/HCOMPASS/%.su Src/HAL/HCOMPASS/%.cyclo: ../Src/HAL/HCOMPASS/%.c Src/HAL/HCOMPASS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-HCOMPASS

clean-Src-2f-HAL-2f-HCOMPASS:
	-$(RM) ./Src/HAL/HCOMPASS/HAL_COMPASS.cyclo ./Src/HAL/HCOMPASS/HAL_COMPASS.d ./Src/HAL/HCOMPASS/HAL_COMPASS.o ./Src/HAL/HCOMPASS/HAL_COMPASS.su

.PHONY: clean-Src-2f-HAL-2f-HCOMPASS

