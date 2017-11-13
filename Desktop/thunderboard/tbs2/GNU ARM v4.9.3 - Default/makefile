################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include protocol/bluetooth_2.6/lib/EFR32MG12P/EABI/subdir.mk
-include platform/emlib/src/subdir.mk
-include platform/emdrv/gpiointerrupt/src/subdir.mk
-include platform/emdrv/dmadrv/src/subdir.mk
-include platform/Device/SiliconLabs/EFR32MG12P/Source/GCC/subdir.mk
-include hardware/kit/common/drivers/subdir.mk
-include hardware/kit/common/bsp/thunderboard/rfs/subdir.mk
-include hardware/kit/common/bsp/thunderboard/imu/subdir.mk
-include hardware/kit/common/bsp/thunderboard/bosch/BMP280_driver/subdir.mk
-include hardware/kit/common/bsp/thunderboard/subdir.mk
-include hardware/kit/common/bsp/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: soc-thunderboard-sense-2.axf

# Tool invocations
soc-thunderboard-sense-2.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -T "C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\efr32mg12p332f1024gl125.ld" -Xlinker -no-enum-size-warning -Xlinker -no-wchar-size-warning -Xlinker --gc-sections -Xlinker -Map="soc-thunderboard-sense-2.map" -mfpu=fpv4-sp-d16 -mfloat-abi=hard -o soc-thunderboard-sense-2.axf "./advertisement-callback.o" "./aio.o" "./app.o" "./app_ble.o" "./app_ble_adv.o" "./app_callback.o" "./application_properties.o" "./batt.o" "./connection-callback.o" "./connection.o" "./es.o" "./gatt_db.o" "./hallservice.o" "./iaq.o" "./imus.o" "./main.o" "./power.o" "./pti.o" "./radio_ble.o" "./timedelay.o" "./ui.o" "./hardware/kit/common/bsp/bsp_stk.o" "./hardware/kit/common/bsp/thunderboard/bap.o" "./hardware/kit/common/bsp/thunderboard/board_4166.o" "./hardware/kit/common/bsp/thunderboard/ccs811.o" "./hardware/kit/common/bsp/thunderboard/hall.o" "./hardware/kit/common/bsp/thunderboard/hall_si7210.o" "./hardware/kit/common/bsp/thunderboard/icm20648.o" "./hardware/kit/common/bsp/thunderboard/mic_i2s.o" "./hardware/kit/common/bsp/thunderboard/si1133.o" "./hardware/kit/common/bsp/thunderboard/si7021.o" "./hardware/kit/common/bsp/thunderboard/util.o" "./hardware/kit/common/bsp/thunderboard/util_supply.o" "./hardware/kit/common/bsp/thunderboard/bosch/BMP280_driver/bmp280.o" "./hardware/kit/common/bsp/thunderboard/imu/imu.o" "./hardware/kit/common/bsp/thunderboard/imu/imu_dcm.o" "./hardware/kit/common/bsp/thunderboard/imu/imu_fuse.o" "./hardware/kit/common/bsp/thunderboard/imu/imu_math.o" "./hardware/kit/common/bsp/thunderboard/rfs/rfs.o" "./hardware/kit/common/drivers/i2cspm.o" "./hardware/kit/common/drivers/retargetio.o" "./hardware/kit/common/drivers/retargetserial.o" "./platform/Device/SiliconLabs/EFR32MG12P/Source/GCC/startup_efr32mg12p.o" "./platform/emdrv/dmadrv/src/dmadrv.o" "./platform/emdrv/gpiointerrupt/src/gpiointerrupt.o" "./platform/emlib/src/em_adc.o" "./platform/emlib/src/em_cmu.o" "./platform/emlib/src/em_cryotimer.o" "./platform/emlib/src/em_gpio.o" "./platform/emlib/src/em_i2c.o" "./platform/emlib/src/em_ldma.o" "./platform/emlib/src/em_leuart.o" "./platform/emlib/src/em_msc.o" "./platform/emlib/src/em_prs.o" "./platform/emlib/src/em_rtcc.o" "./platform/emlib/src/em_system.o" "./platform/emlib/src/em_timer.o" "./platform/emlib/src/em_usart.o" "C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\protocol\bluetooth_2.6\lib\EFR32MG12P\EABI\stack.a" "C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\protocol\bluetooth_2.6\lib\EFR32MG12P\EABI\binstack.o" "C:\Users\danie\SimplicityStudio\v4_workspace\soc-thunderboard-sense-2\protocol\bluetooth_2.6\lib\EFR32MG12P\GCC\bgapi.a" -lm -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: soc-thunderboard-sense-2.hex'
	arm-none-eabi-objcopy -O ihex "soc-thunderboard-sense-2.axf" "soc-thunderboard-sense-2.hex"
	@echo ' '

	@echo 'Building bin file: soc-thunderboard-sense-2.bin'
	arm-none-eabi-objcopy -O binary "soc-thunderboard-sense-2.axf" "soc-thunderboard-sense-2.bin"
	@echo ' '

	@echo 'Building s37 file: soc-thunderboard-sense-2.s37'
	arm-none-eabi-objcopy -O srec "soc-thunderboard-sense-2.axf" "soc-thunderboard-sense-2.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "soc-thunderboard-sense-2.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) soc-thunderboard-sense-2.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
