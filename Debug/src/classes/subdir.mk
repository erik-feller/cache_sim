################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/classes/Cache.cpp \
../src/classes/CacheSystem.cpp \
../src/classes/Dictionary.cpp \
../src/classes/L1.cpp \
../src/classes/L2.cpp \
../src/classes/LRU.cpp \
../src/classes/Memory.cpp \
../src/classes/Victim.cpp \
../src/classes/Way.cpp \
../src/classes/conf_parser.cpp 

OBJS += \
./src/classes/Cache.o \
./src/classes/CacheSystem.o \
./src/classes/Dictionary.o \
./src/classes/L1.o \
./src/classes/L2.o \
./src/classes/LRU.o \
./src/classes/Memory.o \
./src/classes/Victim.o \
./src/classes/Way.o \
./src/classes/conf_parser.o 

CPP_DEPS += \
./src/classes/Cache.d \
./src/classes/CacheSystem.d \
./src/classes/Dictionary.d \
./src/classes/L1.d \
./src/classes/L2.d \
./src/classes/LRU.d \
./src/classes/Memory.d \
./src/classes/Victim.d \
./src/classes/Way.d \
./src/classes/conf_parser.d 


# Each subdirectory must supply rules for building sources it contributes
src/classes/%.o: ../src/classes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


