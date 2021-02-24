################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Timer1.c \
../UART.c \
../external_eeprom.c \
../i2c.c \
../lcd.c \
../uC2.c 

OBJS += \
./Timer1.o \
./UART.o \
./external_eeprom.o \
./i2c.o \
./lcd.o \
./uC2.o 

C_DEPS += \
./Timer1.d \
./UART.d \
./external_eeprom.d \
./i2c.d \
./lcd.d \
./uC2.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


