################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RTE/rte_signal_if.c 

OBJS += \
./RTE/rte_signal_if.o 

C_DEPS += \
./RTE/rte_signal_if.d 


# Each subdirectory must supply rules for building sources it contributes
RTE/%.o RTE/%.su RTE/%.cyclo: ../RTE/%.c RTE/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"C:/Users/HP/Documents/Automotive_ECU_FW/RTE" -I../Core/Inc -IC:/Users/HP/Documents/Automotive_ECU_FW/DeviceDrivers/DS18B20 -I../Drivers/STM32F1xx_HAL_Driver/Inc -IC:/Users/HP/Documents/Automotive_ECU_FW/BSP -IC:/Users/HP/Documents/Automotive_ECU_FW/Application -IC:/Users/HP/Documents/Automotive_ECU_FW/Services -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -IC:/Users/HP/Documents/Automotive_ECU_FW/Config -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-RTE

clean-RTE:
	-$(RM) ./RTE/rte_signal_if.cyclo ./RTE/rte_signal_if.d ./RTE/rte_signal_if.o ./RTE/rte_signal_if.su

.PHONY: clean-RTE

