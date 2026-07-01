################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/bsp_led.c 

OBJS += \
./BSP/bsp_led.o 

C_DEPS += \
./BSP/bsp_led.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/%.o BSP/%.su BSP/%.cyclo: ../BSP/%.c BSP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -IC:/Users/HP/Documents/Automotive_ECU_FW/BSP -IC:/Users/HP/Documents/Automotive_ECU_FW/Application -IC:/Users/HP/Documents/Automotive_ECU_FW/Services -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -IC:/Users/HP/Documents/Automotive_ECU_FW/Config -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BSP

clean-BSP:
	-$(RM) ./BSP/bsp_led.cyclo ./BSP/bsp_led.d ./BSP/bsp_led.o ./BSP/bsp_led.su

.PHONY: clean-BSP

