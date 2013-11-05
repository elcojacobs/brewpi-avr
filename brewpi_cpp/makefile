
# makefile for regular gcc build

# convert build parameters to defines

# simulator flag control by shield type - the simulator is a virtual shield
BREWPI_SIMULATOR = 1

## build target directory organization and output files

# base name of output files
TARGET_NAME ?= brewpi-avr

# location of .cpp sources
AVRSRC=../brewpi_avr/
SRC=./

# temporary .o and .d files
OBJ_DIR = tmp/

# location of artefacts to keep
OUTPUT_DIR ?= tmp/

# default locations for tools based on the toolchain bin dir
AVRGCC ?= $(TOOLCHAIN_BIN)g++$(EXE)

# default config if nothing else specified
BREWPI_STATIC_CONFIG ?= BREWPI_SHIELD_REV_C
BREWPI_DEBUG ?= 0
BUILD_NUMBER ?= 0

DEFINES = \
 -DBREWPI_STATIC_CONFIG=$(BREWPI_STATIC_CONFIG) \
 -DBREWPI_DEBUG=$(BREWPI_DEBUG) \
 -DBREWPI_SIMULATE="1" \
 -DBUILD_NUMBER=$(BUILD_NUMBER) \
 -DBREWPI_DEBUG=1

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
$(SRC)fallback


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
$(AVRSRC)Actuator.cpp \
$(AVRSRC)Brewpi.cpp \
$(AVRSRC)BrewpiStrings.cpp \
$(AVRSRC)Buzzer.cpp \
$(AVRSRC)DeviceManager.cpp \
$(AVRSRC)Display.cpp \
$(AVRSRC)EepromManager.cpp \
$(AVRSRC)FilterCascaded.cpp \
$(AVRSRC)FilterFixed.cpp \
$(AVRSRC)Logger.cpp \
$(SRC)Main.cpp \
$(AVRSRC)Menu.cpp \
$(AVRSRC)NullLcdDriver.cpp \
$(AVRSRC)PiLink.cpp \
$(SRC)Print.cpp \
$(AVRSRC)RotaryEncoder.cpp \
$(AVRSRC)Sensor.cpp \
$(AVRSRC)SettingsManager.cpp \
$(AVRSRC)Simulator.cpp \
$(AVRSRC)TempControl.cpp \
$(AVRSRC)TemperatureFormats.cpp \
$(AVRSRC)TempSensor.cpp \
$(AVRSRC)Ticks.cpp \
$(SRC)timems.cpp


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
$(OBJ_DIR)Actuator.o \
$(OBJ_DIR)Brewpi.o \
$(OBJ_DIR)BrewpiStrings.o \
$(OBJ_DIR)Buzzer.o \
$(OBJ_DIR)DeviceManager.o \
$(OBJ_DIR)Display.o \
$(OBJ_DIR)DisplayLcd.o \
$(OBJ_DIR)EepromManager.o \
$(OBJ_DIR)FilterCascaded.o \
$(OBJ_DIR)FilterFixed.o \
$(OBJ_DIR)Logger.o \
$(OBJ_DIR)Menu.o \
$(OBJ_DIR)Main.o \
$(OBJ_DIR)NullLcdDriver.o \
$(OBJ_DIR)PiLink.o \
$(OBJ_DIR)Print.o \
$(OBJ_DIR)RotaryEncoder.o \
$(OBJ_DIR)Sensor.o \
$(OBJ_DIR)SettingsManager.o \
$(OBJ_DIR)Simulator.o \
$(OBJ_DIR)TempControl.o \
$(OBJ_DIR)TemperatureFormats.o \
$(OBJ_DIR)TempSensor.o \
$(OBJ_DIR)Ticks.o \
$(OBJ_DIR)timems.o

OBJS_AS_ARGS +=  \
$(OBJ_DIR)Actuator.o \
$(OBJ_DIR)Brewpi.o \
$(OBJ_DIR)BrewpiStrings.o \
$(OBJ_DIR)Buzzer.o \
$(OBJ_DIR)DeviceManager.o \
$(OBJ_DIR)Display.o \
$(OBJ_DIR)DisplayLcd.o \
$(OBJ_DIR)EepromManager.o \
$(OBJ_DIR)FilterCascaded.o \
$(OBJ_DIR)FilterFixed.o \
$(OBJ_DIR)Logger.o \
$(OBJ_DIR)Main.o \
$(OBJ_DIR)Menu.o \
$(OBJ_DIR)NullLcdDriver.o \
$(OBJ_DIR)PiLink.o \
$(OBJ_DIR)Print.o \
$(OBJ_DIR)RotaryEncoder.o \
$(OBJ_DIR)Sensor.o \
$(OBJ_DIR)SettingsManager.o \
$(OBJ_DIR)Simulator.o \
$(OBJ_DIR)TempControl.o \
$(OBJ_DIR)TemperatureFormats.o \
$(OBJ_DIR)TempSensor.o \
$(OBJ_DIR)Ticks.o \
$(OBJ_DIR)timems.o


C_DEPS +=  \
$(OBJ_DIR)Actuator.d \
$(OBJ_DIR)Brewpi.d \
$(OBJ_DIR)BrewpiStrings.d \
$(OBJ_DIR)Buzzer.d \
$(OBJ_DIR)DeviceManager.d \
$(OBJ_DIR)Display.d \
$(OBJ_DIR)EepromManager.d \
$(OBJ_DIR)FilterCascaded.d \
$(OBJ_DIR)FilterFixed.d \
$(OBJ_DIR)Logger.d \
$(OBJ_DIR)Menu.d \
$(OBJ_DIR)OLEDFourBit.d \
$(OBJ_DIR)PiLink.d \
$(OBJ_DIR)Print.d \
$(OBJ_DIR)RotaryEncoder.d \
$(OBJ_DIR)Sensor.d \
$(OBJ_DIR)SettingsManager.d \
$(OBJ_DIR)Simulator.d \
$(OBJ_DIR)TempControl.d \
$(OBJ_DIR)TemperatureFormats.d \
$(OBJ_DIR)TempSensor.d \
$(OBJ_DIR)Ticks.d \
$(OBJ_DIR)timems.d \

C_DEPS_AS_ARGS +=  \
$(OBJ_DIR)Actuator.d \
$(OBJ_DIR)Brewpi.d \
$(OBJ_DIR)BrewpiStrings.d \
$(OBJ_DIR)Buzzer.d \
$(OBJ_DIR)DeviceManager.d \
$(OBJ_DIR)Display.d \
$(OBJ_DIR)EepromManager.d \
$(OBJ_DIR)FilterCascaded.d \
$(OBJ_DIR)FilterFixed.d \
$(OBJ_DIR)Logger.d \
$(OBJ_DIR)Menu.d \
$(OBJ_DIR)OLEDFourBit.d \
$(OBJ_DIR)PiLink.d \
$(OBJ_DIR)Print.d \
$(OBJ_DIR)RotaryEncoder.d \
$(OBJ_DIR)Sensor.d \
$(OBJ_DIR)SettingsManager.d \
$(OBJ_DIR)Simulator.d \
$(OBJ_DIR)TempControl.d \
$(OBJ_DIR)TemperatureFormats.d \
$(OBJ_DIR)TempSensor.d \
$(OBJ_DIR)Ticks.d \
$(OBJ_DIR)timems.d

OUTPUT_FILE_PATH +=$(OUTPUT_DIR)$(TARGET_NAME).exe

OUTPUT_FILE_PATH_AS_ARGS +=$(OUTPUT_DIR)$(TARGET_NAME).exe

ADDITIONAL_DEPENDENCIES:=

#OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

# AVR32/GNU C Compiler


#
# Recipes
#

# removed -fpack-struct 
define cppCompile
	@echo Building file: $<
	@echo Invoking: GNU GCC Compiler
	"$(AVRGCC)" $(DEFINES) -Os -I"." -I"$(AVRSRC)" -g -funsigned-char -fshort-enums -Wall  -c -MMD -MP -MF "$(@:%.o=%.d)"  -o "$@" "$(OBJ_DIR)" "$<"
	@echo Finished building: $<
endef	

./$(OBJ_DIR)timems.o: ./$(SRC)timems.cpp
	$(cppCompile)

./$(OBJ_DIR)Print.o: ./$(SRC)Print.cpp
	$(cppCompile)
	
./$(OBJ_DIR)Main.o: ./$(SRC)Main.cpp
	$(cppCompile)

./$(OBJ_DIR)%.o: $(AVRSRC)./%.cpp
	$(cppCompile)
	
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

# removed -Wl,--gc-sections -Wl,-lm  -Wl,--verbose
$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP)
	@echo Building target: $@
	@echo Invoking: GNU Linker
	"$(AVRGCC)" -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -static
	@echo Finished building target: $@

# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	-$(RM) "$(OUTPUT_DIR)$(TARGET_NAME)exe" "$(OUTPUT_DIR)$(TARGET_NAME).a" 
