################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DeviceDrivers/DS18B20/ds18b20.c 

OBJS += \
./DeviceDrivers/DS18B20/ds18b20.o 

C_DEPS += \
./DeviceDrivers/DS18B20/ds18b20.d 


# Each subdirectory must supply rules for building sources it contributes
DeviceDrivers/DS18B20/%.o DeviceDrivers/DS18B20/%.su DeviceDrivers/DS18B20/%.cyclo: ../DeviceDrivers/DS18B20/%.c DeviceDrivers/DS18B20/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"C:/Users/HP/Documents/Automotive_ECU_FW/RTE" -I../Core/Inc -IC:/Users/HP/Documents/Automotive_ECU_FW/DeviceDrivers/DS18B20 -I../Drivers/STM32F1xx_HAL_Driver/Inc -IC:/Users/HP/Documents/Automotive_ECU_FW/BSP -IC:/Users/HP/Documents/Automotive_ECU_FW/Application -IC:/Users/HP/Documents/Automotive_ECU_FW/Services -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -IC:/Users/HP/Documents/Automotive_ECU_FW/Config -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-DeviceDrivers-2f-DS18B20

clean-DeviceDrivers-2f-DS18B20:
	-$(RM) ./DeviceDrivers/DS18B20/ds18b20.cyclo ./DeviceDrivers/DS18B20/ds18b20.d ./DeviceDrivers/DS18B20/ds18b20.o ./DeviceDrivers/DS18B20/ds18b20.su

.PHONY: clean-DeviceDrivers-2f-DS18B20

