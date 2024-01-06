################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Drv_Motor/bouton.c \
../Core/Drv_Motor/encoder.c \
../Core/Drv_Motor/pwm.c \
../Core/Drv_Motor/task.c 

OBJS += \
./Core/Drv_Motor/bouton.o \
./Core/Drv_Motor/encoder.o \
./Core/Drv_Motor/pwm.o \
./Core/Drv_Motor/task.o 

C_DEPS += \
./Core/Drv_Motor/bouton.d \
./Core/Drv_Motor/encoder.d \
./Core/Drv_Motor/pwm.d \
./Core/Drv_Motor/task.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Drv_Motor/%.o Core/Drv_Motor/%.su Core/Drv_Motor/%.cyclo: ../Core/Drv_Motor/%.c Core/Drv_Motor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G070xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/serva/Documents/ESE/Projet/Moteur_Pojet/Motor_projet/Moteur_Pojet/Drivers" -I"C:/Users/serva/Documents/ESE/Projet/Moteur_Pojet/Motor_projet/Moteur_Pojet/Core/Drv_Motor" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Drv_Motor

clean-Core-2f-Drv_Motor:
	-$(RM) ./Core/Drv_Motor/bouton.cyclo ./Core/Drv_Motor/bouton.d ./Core/Drv_Motor/bouton.o ./Core/Drv_Motor/bouton.su ./Core/Drv_Motor/encoder.cyclo ./Core/Drv_Motor/encoder.d ./Core/Drv_Motor/encoder.o ./Core/Drv_Motor/encoder.su ./Core/Drv_Motor/pwm.cyclo ./Core/Drv_Motor/pwm.d ./Core/Drv_Motor/pwm.o ./Core/Drv_Motor/pwm.su ./Core/Drv_Motor/task.cyclo ./Core/Drv_Motor/task.d ./Core/Drv_Motor/task.o ./Core/Drv_Motor/task.su

.PHONY: clean-Core-2f-Drv_Motor

