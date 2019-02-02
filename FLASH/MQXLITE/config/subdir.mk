################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../MQXLITE/config/task_template_list.c" \

C_SRCS += \
../MQXLITE/config/task_template_list.c \

OBJS += \
./MQXLITE/config/task_template_list.o \

C_DEPS += \
./MQXLITE/config/task_template_list.d \

OBJS_QUOTED += \
"./MQXLITE/config/task_template_list.o" \

C_DEPS_QUOTED += \
"./MQXLITE/config/task_template_list.d" \

OBJS_OS_FORMAT += \
./MQXLITE/config/task_template_list.o \


# Each subdirectory must supply rules for building sources it contributes
MQXLITE/config/task_template_list.o: ../MQXLITE/config/task_template_list.c
	@echo 'Building file: $<'
	@echo 'Executing target #52 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"MQXLITE/config/task_template_list.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"MQXLITE/config/task_template_list.o"
	@echo 'Finished building: $<'
	@echo ' '


