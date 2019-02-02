################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/ADC_Handler.c" \
"../Sources/ADC_Lookup.c" \
"../Sources/Application.c" \
"../Sources/Digital_IO.c" \
"../Sources/Display_HL.c" \
"../Sources/Events.c" \
"../Sources/Global_Config.c" \
"../Sources/Keyhandler.c" \
"../Sources/Tasks.c" \
"../Sources/Timer.c" \
"../Sources/main.c" \
"../Sources/mqx_tasks.c" \

C_SRCS += \
../Sources/ADC_Handler.c \
../Sources/ADC_Lookup.c \
../Sources/Application.c \
../Sources/Digital_IO.c \
../Sources/Display_HL.c \
../Sources/Events.c \
../Sources/Global_Config.c \
../Sources/Keyhandler.c \
../Sources/Tasks.c \
../Sources/Timer.c \
../Sources/main.c \
../Sources/mqx_tasks.c \

OBJS += \
./Sources/ADC_Handler.o \
./Sources/ADC_Lookup.o \
./Sources/Application.o \
./Sources/Digital_IO.o \
./Sources/Display_HL.o \
./Sources/Events.o \
./Sources/Global_Config.o \
./Sources/Keyhandler.o \
./Sources/Tasks.o \
./Sources/Timer.o \
./Sources/main.o \
./Sources/mqx_tasks.o \

C_DEPS += \
./Sources/ADC_Handler.d \
./Sources/ADC_Lookup.d \
./Sources/Application.d \
./Sources/Digital_IO.d \
./Sources/Display_HL.d \
./Sources/Events.d \
./Sources/Global_Config.d \
./Sources/Keyhandler.d \
./Sources/Tasks.d \
./Sources/Timer.d \
./Sources/main.d \
./Sources/mqx_tasks.d \

OBJS_QUOTED += \
"./Sources/ADC_Handler.o" \
"./Sources/ADC_Lookup.o" \
"./Sources/Application.o" \
"./Sources/Digital_IO.o" \
"./Sources/Display_HL.o" \
"./Sources/Events.o" \
"./Sources/Global_Config.o" \
"./Sources/Keyhandler.o" \
"./Sources/Tasks.o" \
"./Sources/Timer.o" \
"./Sources/main.o" \
"./Sources/mqx_tasks.o" \

C_DEPS_QUOTED += \
"./Sources/ADC_Handler.d" \
"./Sources/ADC_Lookup.d" \
"./Sources/Application.d" \
"./Sources/Digital_IO.d" \
"./Sources/Display_HL.d" \
"./Sources/Events.d" \
"./Sources/Global_Config.d" \
"./Sources/Keyhandler.d" \
"./Sources/Tasks.d" \
"./Sources/Timer.d" \
"./Sources/main.d" \
"./Sources/mqx_tasks.d" \

OBJS_OS_FORMAT += \
./Sources/ADC_Handler.o \
./Sources/ADC_Lookup.o \
./Sources/Application.o \
./Sources/Digital_IO.o \
./Sources/Display_HL.o \
./Sources/Events.o \
./Sources/Global_Config.o \
./Sources/Keyhandler.o \
./Sources/Tasks.o \
./Sources/Timer.o \
./Sources/main.o \
./Sources/mqx_tasks.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/ADC_Handler.o: ../Sources/ADC_Handler.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/ADC_Handler.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/ADC_Handler.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/ADC_Lookup.o: ../Sources/ADC_Lookup.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/ADC_Lookup.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/ADC_Lookup.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Application.o: ../Sources/Application.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Application.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Application.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Digital_IO.o: ../Sources/Digital_IO.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Digital_IO.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Digital_IO.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Display_HL.o: ../Sources/Display_HL.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Display_HL.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Display_HL.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Events.o: ../Sources/Events.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Events.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Events.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Global_Config.o: ../Sources/Global_Config.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Global_Config.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Global_Config.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Keyhandler.o: ../Sources/Keyhandler.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Keyhandler.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Keyhandler.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Tasks.o: ../Sources/Tasks.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Tasks.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Tasks.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Timer.o: ../Sources/Timer.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Timer.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Timer.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/mqx_tasks.o: ../Sources/mqx_tasks.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/mqx_tasks.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/mqx_tasks.o"
	@echo 'Finished building: $<'
	@echo ' '


