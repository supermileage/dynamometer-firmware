SRC_DIR = src/
LIB_DIR = lib/
TEST_DIR = test/
OBJ_DIR = $(TEST_DIR)obj/
DEP_DIR = $(TEST_DIR)dep/
BIN_DIR = $(TEST_DIR)bin/

# SRC TEST FILES -- Only these files will be compiled for tests
SENSOR := Sensor/SensorOptical.cpp 

# All files to compile for tests
TEST_DIRS := $(dir $(wildcard $(TEST_DIR)tests/*/))
TEST_CPP_TEMP := $(patsubst $(TEST_DIR)%,%,$(foreach %,$(TEST_DIRS),$(wildcard $(%)*.cpp)))
SRC_CPP_TEMP := $(SENSOR)

# ALL TEST FILES
CPP_TO_OBJ := $(SRC_CPP_TEMP) $(TEST_CPP_TEMP) test.cpp
TEST_OBJ := $(patsubst %.cpp,%.o,$(foreach %,$(CPP_TO_OBJ),$(OBJ_DIR)$(%)))
TEST_CPP := $(foreach %,$(SRC_CPP_TEMP),$(SRC_DIR)$(%)) $(foreach %,$(TEST_CPP_TEMP),$(TEST_DIR)$(%)) $(TEST_DIR)test.cpp

# ALL TEST INCLUDE DIRS
TEST_DIRS += $(TEST_DIR)