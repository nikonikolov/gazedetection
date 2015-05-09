################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../process_loci/process_loci.cpp 

OBJS += \
./process_loci/process_loci.o 

CPP_DEPS += \
./process_loci/process_loci.d 


# Each subdirectory must supply rules for building sources it contributes
process_loci/%.o: ../process_loci/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/ros/indigo/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


