################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Inc/Startup/startup_stm32f407vgtx.s 

OBJS += \
./Core/Inc/Startup/startup_stm32f407vgtx.o 

S_DEPS += \
./Core/Inc/Startup/startup_stm32f407vgtx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/Startup/%.o: ../Core/Inc/Startup/%.s Core/Inc/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Inc-2f-Startup

clean-Core-2f-Inc-2f-Startup:
	-$(RM) ./Core/Inc/Startup/startup_stm32f407vgtx.d ./Core/Inc/Startup/startup_stm32f407vgtx.o

.PHONY: clean-Core-2f-Inc-2f-Startup

