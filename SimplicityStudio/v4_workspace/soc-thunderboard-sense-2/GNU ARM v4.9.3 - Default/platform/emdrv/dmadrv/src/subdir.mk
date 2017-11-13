################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/emdrv/dmadrv/src/dmadrv.c 

OBJS += \
./platform/emdrv/dmadrv/src/dmadrv.o 

C_DEPS += \
./platform/emdrv/dmadrv/src/dmadrv.d 


# Each subdirectory must supply rules for building sources it contributes
platform/emdrv/dmadrv/src/dmadrv.o: ../platform/emdrv/dmadrv/src/dmadrv.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DRADIO_BLE=1' '-D__NO_SYSTEM_INIT=1' '-DEFR32MG12P332F1024GL125=1' -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\platform\CMSIS\Include" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\platform\Device\SiliconLabs\EFR32MG12P\Include" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\platform\bootloader\api" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\platform\emlib\inc" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\hardware\kit\common\drivers" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\platform\emdrv\dmadrv\src" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\hardware\kit\common\bsp\thunderboard" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\platform\emdrv\common\inc" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\platform\emlib\src" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\protocol\bluetooth_2.6\ble_stack\inc\common" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\platform\emdrv\dmadrv\inc" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\hardware\kit\common\bsp\thunderboard\imu" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\hardware\kit\EFR32MG12_BRD4166A\config" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\hardware\kit\common\bsp\thunderboard\rfs" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\app\bluetooth_2.6\common\stack_bridge" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\platform\radio\rail_lib\common" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\hardware\kit\common\bsp\thunderboard\bosch\BMP280_driver" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\protocol\bluetooth_2.6\ble_stack\inc\soc" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\platform\Device\SiliconLabs\EFR32MG12P\Source\GCC" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\hardware\kit\common\bsp" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\platform\emdrv\uartdrv\inc" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\platform\emdrv\sleep\inc" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\platform\radio\rail_lib\chip\efr32" -I"C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\platform\emdrv\gpiointerrupt\src" -O2 -fno-short-enums -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=hard -MMD -MP -MF"platform/emdrv/dmadrv/src/dmadrv.d" -MT"platform/emdrv/dmadrv/src/dmadrv.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


