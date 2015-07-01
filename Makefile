ROOT_DIR = $(abspath ..)

# compile options ##############################################################
CFLAGS +=
CXXFLAGS +=

# sources ######################################################################
PROJ_NAME := GuruxDLMSLibServerExample
PROJ_ROOT_DIR := $(abspath .)
PROJ_SOURCE_DIR := ${PROJ_ROOT_DIR}
PROJ_BUILD_DIR := ${PROJ_ROOT_DIR}/build
PROJ_OBJ_DIR := ${PROJ_BUILD_DIR}/obj

INCLUDE += \
	-I ${PROJ_ROOT_DIR}/include \
	-I ${PROJ_ROOT_DIR}

OBJS += \
	${PROJ_OBJ_DIR}/GuruxDLMSLibServerExample.o \
	${PROJ_OBJ_DIR}/GXDLMSBase.o \
	${PROJ_OBJ_DIR}/GXNet.o \
	${PROJ_OBJ_DIR}/stdafx.o \

INCLUDE += \
	-I ${ROOT_DIR}/include

LIB += \
	-L${ROOT_DIR}/GuruxDLMSLib/lib \
	-lGuruxDLMSLib \
	-lpthread \

include tools.mk

################################################################################
PROJ_BIN_DIR := ${PROJ_ROOT_DIR}/bin
PROJ_BIN := ${PROJ_BIN_DIR}/${PROJ_NAME}

# targets ######################################################################
.PHONY: all always bin clean
.INTERMEDIATE: ${DEPS}

all: bin

always:

bin: ${PROJ_BIN}

clean:
	@rm -rf \
		${PROJ_OBJ_DIR} \
		${PROJ_TEST_OBJ_DIR} \
		${PROJ_BIN_DIR} \

# bin targets ##################################################################
${PROJ_BIN}: always ${OBJS}
	@printf "Linking $@\n"
	@mkdir -p "$(dir $@)"
	@${CXX} -o $@ ${OBJS} ${LIB}
	@${STRIP} $@

${PROJ_OBJ_DIR}/%.o: ${PROJ_SOURCE_DIR}/%.cpp
	@printf "Compiling $<\n"
	@mkdir -p "$(dir $@)"
	@${CXX} \
		-o $@ \
		-c \
		${INCLUDE} \
		${CXXFLAGS} \
		$<
