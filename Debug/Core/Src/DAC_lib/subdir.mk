################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/DAC_lib/DAC_lib.c 

OBJS += \
./Core/Src/DAC_lib/DAC_lib.o 

C_DEPS += \
./Core/Src/DAC_lib/DAC_lib.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/DAC_lib/%.o Core/Src/DAC_lib/%.su Core/Src/DAC_lib/%.cyclo: ../Core/Src/DAC_lib/%.c Core/Src/DAC_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-DAC_lib

clean-Core-2f-Src-2f-DAC_lib:
	-$(RM) ./Core/Src/DAC_lib/DAC_lib.cyclo ./Core/Src/DAC_lib/DAC_lib.d ./Core/Src/DAC_lib/DAC_lib.o ./Core/Src/DAC_lib/DAC_lib.su

.PHONY: clean-Core-2f-Src-2f-DAC_lib

