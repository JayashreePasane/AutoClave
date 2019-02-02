################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS_QUOTED += \
"../MQXLITE/psp/cortex_m/core/M4/boot.S" \
"../MQXLITE/psp/cortex_m/core/M4/dispatch.S" \

S_UPPER_SRCS += \
../MQXLITE/psp/cortex_m/core/M4/boot.S \
../MQXLITE/psp/cortex_m/core/M4/dispatch.S \

OBJS += \
./MQXLITE/psp/cortex_m/core/M4/boot.o \
./MQXLITE/psp/cortex_m/core/M4/dispatch.o \

S_UPPER_DEPS += \
./MQXLITE/psp/cortex_m/core/M4/boot.d \
./MQXLITE/psp/cortex_m/core/M4/dispatch.d \

OBJS_QUOTED += \
"./MQXLITE/psp/cortex_m/core/M4/boot.o" \
"./MQXLITE/psp/cortex_m/core/M4/dispatch.o" \

S_UPPER_DEPS_QUOTED += \
"./MQXLITE/psp/cortex_m/core/M4/boot.d" \
"./MQXLITE/psp/cortex_m/core/M4/dispatch.d" \

OBJS_OS_FORMAT += \
./MQXLITE/psp/cortex_m/core/M4/boot.o \
./MQXLITE/psp/cortex_m/core/M4/dispatch.o \


# Each subdirectory must supply rules for building sources it contributes
MQXLITE/psp/cortex_m/core/M4/boot.o: ../MQXLITE/psp/cortex_m/core/M4/boot.S
	@echo 'Building file: $<'
	@echo 'Executing target #34 $<'
	@echo 'Invoking: ARM Ltd Windows GCC Assembler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"MQXLITE/psp/cortex_m/core/M4/boot.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"MQXLITE/psp/cortex_m/core/M4/boot.o"
	@echo 'Finished building: $<'
	@echo ' '

MQXLITE/psp/cortex_m/core/M4/dispatch.o: ../MQXLITE/psp/cortex_m/core/M4/dispatch.S
	@echo 'Building file: $<'
	@echo 'Executing target #35 $<'
	@echo 'Invoking: ARM Ltd Windows GCC Assembler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"MQXLITE/psp/cortex_m/core/M4/dispatch.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"MQXLITE/psp/cortex_m/core/M4/dispatch.o"
	@echo 'Finished building: $<'
	@echo ' '


