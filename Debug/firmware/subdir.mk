################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../firmware/at32f413_acc.c \
../firmware/at32f413_adc.c \
../firmware/at32f413_bpr.c \
../firmware/at32f413_can.c \
../firmware/at32f413_crc.c \
../firmware/at32f413_crm.c \
../firmware/at32f413_debug.c \
../firmware/at32f413_dma.c \
../firmware/at32f413_exint.c \
../firmware/at32f413_flash.c \
../firmware/at32f413_gpio.c \
../firmware/at32f413_i2c.c \
../firmware/at32f413_misc.c \
../firmware/at32f413_pwc.c \
../firmware/at32f413_rtc.c \
../firmware/at32f413_sdio.c \
../firmware/at32f413_spi.c \
../firmware/at32f413_tmr.c \
../firmware/at32f413_usart.c \
../firmware/at32f413_usb.c \
../firmware/at32f413_wdt.c \
../firmware/at32f413_wwdt.c 

OBJS += \
./firmware/at32f413_acc.o \
./firmware/at32f413_adc.o \
./firmware/at32f413_bpr.o \
./firmware/at32f413_can.o \
./firmware/at32f413_crc.o \
./firmware/at32f413_crm.o \
./firmware/at32f413_debug.o \
./firmware/at32f413_dma.o \
./firmware/at32f413_exint.o \
./firmware/at32f413_flash.o \
./firmware/at32f413_gpio.o \
./firmware/at32f413_i2c.o \
./firmware/at32f413_misc.o \
./firmware/at32f413_pwc.o \
./firmware/at32f413_rtc.o \
./firmware/at32f413_sdio.o \
./firmware/at32f413_spi.o \
./firmware/at32f413_tmr.o \
./firmware/at32f413_usart.o \
./firmware/at32f413_usb.o \
./firmware/at32f413_wdt.o \
./firmware/at32f413_wwdt.o 

C_DEPS += \
./firmware/at32f413_acc.d \
./firmware/at32f413_adc.d \
./firmware/at32f413_bpr.d \
./firmware/at32f413_can.d \
./firmware/at32f413_crc.d \
./firmware/at32f413_crm.d \
./firmware/at32f413_debug.d \
./firmware/at32f413_dma.d \
./firmware/at32f413_exint.d \
./firmware/at32f413_flash.d \
./firmware/at32f413_gpio.d \
./firmware/at32f413_i2c.d \
./firmware/at32f413_misc.d \
./firmware/at32f413_pwc.d \
./firmware/at32f413_rtc.d \
./firmware/at32f413_sdio.d \
./firmware/at32f413_spi.d \
./firmware/at32f413_tmr.d \
./firmware/at32f413_usart.d \
./firmware/at32f413_usb.d \
./firmware/at32f413_wdt.d \
./firmware/at32f413_wwdt.d 


# Each subdirectory must supply rules for building sources it contributes
firmware/%.o: ../firmware/%.c firmware/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections  -g -DAT_START_F413_V1 -DAT32F413C8T7 -DUSE_STDPERIPH_DRIVER -I"../include" -I"../include/libraries/drivers/inc" -I"../include/libraries/cmsis/cm4/core_support" -I"../include/libraries/cmsis/cm4/device_support" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


