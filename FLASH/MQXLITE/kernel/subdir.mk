################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../MQXLITE/kernel/idletask.c" \
"../MQXLITE/kernel/int.c" \
"../MQXLITE/kernel/klog.c" \
"../MQXLITE/kernel/lwevent.c" \
"../MQXLITE/kernel/lwlog.c" \
"../MQXLITE/kernel/lwmem.c" \
"../MQXLITE/kernel/lwmsgq.c" \
"../MQXLITE/kernel/lwsem.c" \
"../MQXLITE/kernel/lwtimer.c" \
"../MQXLITE/kernel/mqx_utils.c" \
"../MQXLITE/kernel/mqxlite.c" \
"../MQXLITE/kernel/mutex.c" \
"../MQXLITE/kernel/qu_test.c" \
"../MQXLITE/kernel/sched.c" \
"../MQXLITE/kernel/task.c" \
"../MQXLITE/kernel/time_ticks.c" \

C_SRCS += \
../MQXLITE/kernel/idletask.c \
../MQXLITE/kernel/int.c \
../MQXLITE/kernel/klog.c \
../MQXLITE/kernel/lwevent.c \
../MQXLITE/kernel/lwlog.c \
../MQXLITE/kernel/lwmem.c \
../MQXLITE/kernel/lwmsgq.c \
../MQXLITE/kernel/lwsem.c \
../MQXLITE/kernel/lwtimer.c \
../MQXLITE/kernel/mqx_utils.c \
../MQXLITE/kernel/mqxlite.c \
../MQXLITE/kernel/mutex.c \
../MQXLITE/kernel/qu_test.c \
../MQXLITE/kernel/sched.c \
../MQXLITE/kernel/task.c \
../MQXLITE/kernel/time_ticks.c \

OBJS += \
./MQXLITE/kernel/idletask.o \
./MQXLITE/kernel/int.o \
./MQXLITE/kernel/klog.o \
./MQXLITE/kernel/lwevent.o \
./MQXLITE/kernel/lwlog.o \
./MQXLITE/kernel/lwmem.o \
./MQXLITE/kernel/lwmsgq.o \
./MQXLITE/kernel/lwsem.o \
./MQXLITE/kernel/lwtimer.o \
./MQXLITE/kernel/mqx_utils.o \
./MQXLITE/kernel/mqxlite.o \
./MQXLITE/kernel/mutex.o \
./MQXLITE/kernel/qu_test.o \
./MQXLITE/kernel/sched.o \
./MQXLITE/kernel/task.o \
./MQXLITE/kernel/time_ticks.o \

C_DEPS += \
./MQXLITE/kernel/idletask.d \
./MQXLITE/kernel/int.d \
./MQXLITE/kernel/klog.d \
./MQXLITE/kernel/lwevent.d \
./MQXLITE/kernel/lwlog.d \
./MQXLITE/kernel/lwmem.d \
./MQXLITE/kernel/lwmsgq.d \
./MQXLITE/kernel/lwsem.d \
./MQXLITE/kernel/lwtimer.d \
./MQXLITE/kernel/mqx_utils.d \
./MQXLITE/kernel/mqxlite.d \
./MQXLITE/kernel/mutex.d \
./MQXLITE/kernel/qu_test.d \
./MQXLITE/kernel/sched.d \
./MQXLITE/kernel/task.d \
./MQXLITE/kernel/time_ticks.d \

OBJS_QUOTED += \
"./MQXLITE/kernel/idletask.o" \
"./MQXLITE/kernel/int.o" \
"./MQXLITE/kernel/klog.o" \
"./MQXLITE/kernel/lwevent.o" \
"./MQXLITE/kernel/lwlog.o" \
"./MQXLITE/kernel/lwmem.o" \
"./MQXLITE/kernel/lwmsgq.o" \
"./MQXLITE/kernel/lwsem.o" \
"./MQXLITE/kernel/lwtimer.o" \
"./MQXLITE/kernel/mqx_utils.o" \
"./MQXLITE/kernel/mqxlite.o" \
"./MQXLITE/kernel/mutex.o" \
"./MQXLITE/kernel/qu_test.o" \
"./MQXLITE/kernel/sched.o" \
"./MQXLITE/kernel/task.o" \
"./MQXLITE/kernel/time_ticks.o" \

C_DEPS_QUOTED += \
"./MQXLITE/kernel/idletask.d" \
"./MQXLITE/kernel/int.d" \
"./MQXLITE/kernel/klog.d" \
"./MQXLITE/kernel/lwevent.d" \
"./MQXLITE/kernel/lwlog.d" \
"./MQXLITE/kernel/lwmem.d" \
"./MQXLITE/kernel/lwmsgq.d" \
"./MQXLITE/kernel/lwsem.d" \
"./MQXLITE/kernel/lwtimer.d" \
"./MQXLITE/kernel/mqx_utils.d" \
"./MQXLITE/kernel/mqxlite.d" \
"./MQXLITE/kernel/mutex.d" \
"./MQXLITE/kernel/qu_test.d" \
"./MQXLITE/kernel/sched.d" \
"./MQXLITE/kernel/task.d" \
"./MQXLITE/kernel/time_ticks.d" \

OBJS_OS_FORMAT += \
./MQXLITE/kernel/idletask.o \
./MQXLITE/kernel/int.o \
./MQXLITE/kernel/klog.o \
./MQXLITE/kernel/lwevent.o \
./MQXLITE/kernel/lwlog.o \
./MQXLITE/kernel/lwmem.o \
./MQXLITE/kernel/lwmsgq.o \
./MQXLITE/kernel/lwsem.o \
./MQXLITE/kernel/lwtimer.o \
./MQXLITE/kernel/mqx_utils.o \
./MQXLITE/kernel/mqxlite.o \
./MQXLITE/kernel/mutex.o \
./MQXLITE/kernel/qu_test.o \
./MQXLITE/kernel/sched.o \
./MQXLITE/kernel/task.o \
./MQXLITE/kernel/time_ticks.o \


# Each subdirectory must supply rules for building sources it contributes
MQXLITE/kernel/idletask.o: ../MQXLITE/kernel/idletask.c
	@echo 'Building file: $<'
	@echo 'Executing target #36 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"MQXLITE/kernel/idletask.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"MQXLITE/kernel/idletask.o"
	@echo 'Finished building: $<'
	@echo ' '

MQXLITE/kernel/int.o: ../MQXLITE/kernel/int.c
	@echo 'Building file: $<'
	@echo 'Executing target #37 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"MQXLITE/kernel/int.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"MQXLITE/kernel/int.o"
	@echo 'Finished building: $<'
	@echo ' '

MQXLITE/kernel/klog.o: ../MQXLITE/kernel/klog.c
	@echo 'Building file: $<'
	@echo 'Executing target #38 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"MQXLITE/kernel/klog.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"MQXLITE/kernel/klog.o"
	@echo 'Finished building: $<'
	@echo ' '

MQXLITE/kernel/lwevent.o: ../MQXLITE/kernel/lwevent.c
	@echo 'Building file: $<'
	@echo 'Executing target #39 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"MQXLITE/kernel/lwevent.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"MQXLITE/kernel/lwevent.o"
	@echo 'Finished building: $<'
	@echo ' '

MQXLITE/kernel/lwlog.o: ../MQXLITE/kernel/lwlog.c
	@echo 'Building file: $<'
	@echo 'Executing target #40 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"MQXLITE/kernel/lwlog.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"MQXLITE/kernel/lwlog.o"
	@echo 'Finished building: $<'
	@echo ' '

MQXLITE/kernel/lwmem.o: ../MQXLITE/kernel/lwmem.c
	@echo 'Building file: $<'
	@echo 'Executing target #41 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"MQXLITE/kernel/lwmem.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"MQXLITE/kernel/lwmem.o"
	@echo 'Finished building: $<'
	@echo ' '

MQXLITE/kernel/lwmsgq.o: ../MQXLITE/kernel/lwmsgq.c
	@echo 'Building file: $<'
	@echo 'Executing target #42 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"MQXLITE/kernel/lwmsgq.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"MQXLITE/kernel/lwmsgq.o"
	@echo 'Finished building: $<'
	@echo ' '

MQXLITE/kernel/lwsem.o: ../MQXLITE/kernel/lwsem.c
	@echo 'Building file: $<'
	@echo 'Executing target #43 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"MQXLITE/kernel/lwsem.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"MQXLITE/kernel/lwsem.o"
	@echo 'Finished building: $<'
	@echo ' '

MQXLITE/kernel/lwtimer.o: ../MQXLITE/kernel/lwtimer.c
	@echo 'Building file: $<'
	@echo 'Executing target #44 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"MQXLITE/kernel/lwtimer.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"MQXLITE/kernel/lwtimer.o"
	@echo 'Finished building: $<'
	@echo ' '

MQXLITE/kernel/mqx_utils.o: ../MQXLITE/kernel/mqx_utils.c
	@echo 'Building file: $<'
	@echo 'Executing target #45 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"MQXLITE/kernel/mqx_utils.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"MQXLITE/kernel/mqx_utils.o"
	@echo 'Finished building: $<'
	@echo ' '

MQXLITE/kernel/mqxlite.o: ../MQXLITE/kernel/mqxlite.c
	@echo 'Building file: $<'
	@echo 'Executing target #46 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"MQXLITE/kernel/mqxlite.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"MQXLITE/kernel/mqxlite.o"
	@echo 'Finished building: $<'
	@echo ' '

MQXLITE/kernel/mutex.o: ../MQXLITE/kernel/mutex.c
	@echo 'Building file: $<'
	@echo 'Executing target #47 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"MQXLITE/kernel/mutex.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"MQXLITE/kernel/mutex.o"
	@echo 'Finished building: $<'
	@echo ' '

MQXLITE/kernel/qu_test.o: ../MQXLITE/kernel/qu_test.c
	@echo 'Building file: $<'
	@echo 'Executing target #48 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"MQXLITE/kernel/qu_test.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"MQXLITE/kernel/qu_test.o"
	@echo 'Finished building: $<'
	@echo ' '

MQXLITE/kernel/sched.o: ../MQXLITE/kernel/sched.c
	@echo 'Building file: $<'
	@echo 'Executing target #49 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"MQXLITE/kernel/sched.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"MQXLITE/kernel/sched.o"
	@echo 'Finished building: $<'
	@echo ' '

MQXLITE/kernel/task.o: ../MQXLITE/kernel/task.c
	@echo 'Building file: $<'
	@echo 'Executing target #50 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"MQXLITE/kernel/task.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"MQXLITE/kernel/task.o"
	@echo 'Finished building: $<'
	@echo ' '

MQXLITE/kernel/time_ticks.o: ../MQXLITE/kernel/time_ticks.c
	@echo 'Building file: $<'
	@echo 'Executing target #51 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"MQXLITE/kernel/time_ticks.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"MQXLITE/kernel/time_ticks.o"
	@echo 'Finished building: $<'
	@echo ' '


