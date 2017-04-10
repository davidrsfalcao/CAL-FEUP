################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algoritmos.cpp \
../src/Alojamento.cpp \
../src/Cidade.cpp \
../src/Coordenadas.cpp \
../src/Epoca.cpp \
../src/Launcher.cpp \
../src/connection.cpp \
../src/graphviewer.cpp \
../src/uteis.cpp 

OBJS += \
./src/Algoritmos.o \
./src/Alojamento.o \
./src/Cidade.o \
./src/Coordenadas.o \
./src/Epoca.o \
./src/Launcher.o \
./src/connection.o \
./src/graphviewer.o \
./src/uteis.o 

CPP_DEPS += \
./src/Algoritmos.d \
./src/Alojamento.d \
./src/Cidade.d \
./src/Coordenadas.d \
./src/Epoca.d \
./src/Launcher.d \
./src/connection.d \
./src/graphviewer.d \
./src/uteis.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


