################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Services/debug.c 

OBJS += \
./Services/debug.o 

C_DEPS += \
./Services/debug.d 


# Each subdirectory must supply rules for building sources it contributes
Services/%.o Services/%.su Services/%.cyclo: ../Services/%.c Services/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"C:/Users/HP/Documents/Automotive_ECU_FW/RTE" -I../Core/Inc -IC:/Users/HP/Documents/Automotive_ECU_FW/DeviceDrivers/DS18B20 -I../Drivers/STM32F1xx_HAL_Driver/Inc -IC:/Users/HP/Documents/Automotive_ECU_FW/BSP -IC:/Users/HP/Documents/Automotive_ECU_FW/Application -IC:/Users/HP/Documents/Automotive_ECU_FW/Services -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -IC:/Users/HP/Documents/Automotive_ECU_FW/Config -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Services

clean-Services:
	-$(RM) ./Services/debug.cyclo ./Services/debug.d ./Services/debug.o ./Services/debug.su

.PHONY: clean-Services

