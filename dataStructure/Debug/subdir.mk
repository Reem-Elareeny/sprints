################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../StackWithLinkedList.c \
../main.c \
../queue.c \
../stack.c 

OBJS += \
./StackWithLinkedList.o \
./main.o \
./queue.o \
./stack.o 

C_DEPS += \
./StackWithLinkedList.d \
./main.d \
./queue.d \
./stack.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


