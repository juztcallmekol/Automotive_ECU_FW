################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/app.c 

OBJS += \
./Application/app.o 

C_DEPS += \
./Application/app.d 


# Each subdirectory must supply rules for building sources it contributes
Application/%.o Application/%.su Application/%.cyclo: ../Application/%.c Application/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -IC:/Users/HP/Documents/Automotive_ECU_FW/BSP -IC:/Users/HP/Documents/Automotive_ECU_FW/Application -IC:/Users/HP/Documents/Automotive_ECU_FW/Services -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -IC:/Users/HP/Documents/Automotive_ECU_FW/Config -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Application

clean-Application:
	-$(RM) ./Application/app.cyclo ./Application/app.d ./Application/app.o ./Application/app.su

.PHONY: clean-Application

