################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../jpeg/jpeg.cpp 

OBJS += \
./jpeg/jpeg.o 

CPP_DEPS += \
./jpeg/jpeg.d 


# Each subdirectory must supply rules for building sources it contributes
jpeg/%.o: ../jpeg/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/ros/indigo/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


