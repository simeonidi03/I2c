################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../user/at32f413_clock.c \
../user/at32f413_int.c \
../user/fonts.c \
../user/main.c \
../user/ssd1306.c \
../user/ssd1306_i2c.c 

OBJS += \
./user/at32f413_clock.o \
./user/at32f413_int.o \
./user/fonts.o \
./user/main.o \
./user/ssd1306.o \
./user/ssd1306_i2c.o 

C_DEPS += \
./user/at32f413_clock.d \
./user/at32f413_int.d \
./user/fonts.d \
./user/main.d \
./user/ssd1306.d \
./user/ssd1306_i2c.d 


# Each subdirectory must supply rules for building sources it contributes
user/%.o: ../user/%.c user/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections  -g -DAT_START_F413_V1 -DAT32F413C8T7 -DUSE_STDPERIPH_DRIVER -I"../include" -I"../include/libraries/drivers/inc" -I"../include/libraries/cmsis/cm4/core_support" -I"../include/libraries/cmsis/cm4/device_support" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


