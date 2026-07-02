################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DeviceDrivers/MPU6050/mpu6050.c 

OBJS += \
./DeviceDrivers/MPU6050/mpu6050.o 

C_DEPS += \
./DeviceDrivers/MPU6050/mpu6050.d 


# Each subdirectory must supply rules for building sources it contributes
DeviceDrivers/MPU6050/%.o DeviceDrivers/MPU6050/%.su DeviceDrivers/MPU6050/%.cyclo: ../DeviceDrivers/MPU6050/%.c DeviceDrivers/MPU6050/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -IC:/Users/HP/Documents/Automotive_ECU_FW/DeviceDrivers/MPU6050 -I../Drivers/STM32F1xx_HAL_Driver/Inc -IC:/Users/HP/Documents/Automotive_ECU_FW/BSP -IC:/Users/HP/Documents/Automotive_ECU_FW/Application -IC:/Users/HP/Documents/Automotive_ECU_FW/Services -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -IC:/Users/HP/Documents/Automotive_ECU_FW/Config -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-DeviceDrivers-2f-MPU6050

clean-DeviceDrivers-2f-MPU6050:
	-$(RM) ./DeviceDrivers/MPU6050/mpu6050.cyclo ./DeviceDrivers/MPU6050/mpu6050.d ./DeviceDrivers/MPU6050/mpu6050.o ./DeviceDrivers/MPU6050/mpu6050.su

.PHONY: clean-DeviceDrivers-2f-MPU6050

