################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../Protocols/ByzantineProtocol.cc \
../Protocols/C01K03Tolerance.cc \
../Protocols/CCo0ETolerance.cc \
../Protocols/CCo1ETolerance.cc \
../Protocols/CCo2ETolerance.cc \
../Protocols/CCo3ETolerance.cc \
../Protocols/CCoInfyETolerance.cc \
../Protocols/CxHopTolerance.cc \
../Protocols/K03Tolerance.cc \
../Protocols/K1HopTolerance.cc \
../Protocols/KCo1Tolerance.cc \
../Protocols/KCo1CCo3Tolerance.cc \
../Protocols/KCo2Tolerance.cc \
../Protocols/KSelfCCo1ETolerance.cc \
../Protocols/KSelfTolerance.cc \
../Protocols/KxHopTolerance.cc \
../Protocols/NetworkProtocol.cc \
../Protocols/ToleranceBase.cc 

OBJS += \
./Protocols/ByzantineProtocol.o \
./Protocols/C01K03Tolerance.o \
./Protocols/CCo0ETolerance.o \
./Protocols/CCo1ETolerance.o \
./Protocols/CCo2ETolerance.o \
./Protocols/CCo3ETolerance.o \
./Protocols/CCoInfyETolerance.o \
./Protocols/CxHopTolerance.o \
./Protocols/K03Tolerance.o \
./Protocols/K1HopTolerance.o \
./Protocols/KCo1Tolerance.o \
./Protocols/KCo1CCo3Tolerance.o \
./Protocols/KCo2Tolerance.o \
./Protocols/KSelfCCo1ETolerance.o \
./Protocols/KSelfTolerance.o \
./Protocols/KxHopTolerance.o \
./Protocols/NetworkProtocol.o \
./Protocols/ToleranceBase.o 

CC_DEPS += \
./Protocols/ByzantineProtocol.d \
./Protocols/C01K03Tolerance.d \
./Protocols/CCo0ETolerance.d \
./Protocols/CCo1ETolerance.d \
./Protocols/CCo2ETolerance.d \
./Protocols/CCo3ETolerance.d \
./Protocols/CCoInfyETolerance.d \
./Protocols/CxHopTolerance.d \
./Protocols/K03Tolerance.d \
./Protocols/K1HopTolerance.d \
./Protocols/KCo1Tolerance.d \
./Protocols/KCo1CCo3Tolerance.d \
./Protocols/KCo2Tolerance.d \
./Protocols/KSelfCCo1ETolerance.d \
./Protocols/KSelfTolerance.d \
./Protocols/KxHopTolerance.d \
./Protocols/NetworkProtocol.d \
./Protocols/ToleranceBase.d 


# Each subdirectory must supply rules for building sources it contributes
Protocols/%.o: ../Protocols/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	CC -I../. -I../Common -I../Domain -I../Deployment -I../Protocols -I../Generators -I../Simulators -I../../boost_1_53_0 -O3 -g -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


