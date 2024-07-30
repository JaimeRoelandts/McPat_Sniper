TARGET = mcpat
SHELL = /bin/sh
.PHONY: all depend clean
.SUFFIXES: .cc .o

SRCS  = \
  Ucache.cc \
  XML_Parse.cc \
  arbiter.cc \
  area.cc \
  array.cc \
  bank.cc \
  basic_circuit.cc \
  basic_components.cc \
  cacti_interface.cc \
  component.cc \
  core.cc \
  crossbar.cc \
  decoder.cc \
  htree2.cc \
  interconnect.cc \
  io.cc \
  iocontrollers.cc \
  logic.cc \
  main.cc \
  mat.cc \
  memoryctrl.cc \
  noc.cc \
  nuca.cc \
  parameter.cc \
  processor.cc \
  router.cc \
  sharedcache.cc \
  subarray.cc \
  technology.cc \
  uca.cc \
  wire.cc \
  xmlParser.cc \
  powergating.cc

OBJS = $(patsubst %.cc,obj_$(TAG)/%.o,$(SRCS))

ifndef NTHREADS
  NTHREADS = 4
endif


LIBS = 
INCS = -lm

ifeq ($(TAG),dbg)
  DBG = -Wall 
  OPT = -ggdb -g -O0 -DNTHREADS=1 -Icacti
else
  DBG = 
  OPT = -Werror -O3 -msse2 -mfpmath=sse -DNTHREADS=$(NTHREADS) -Icacti
  #OPT = -O0 -DNTHREADS=$(NTHREADS)
endif

ifeq ($(ARCH),ia32)
  OPT += -m32
endif

ifneq ($(CACHE),)
  LIBS += -ldb
  OBJS := $(subst io.o,io_cache.o,$(OBJS))
  TARGET:=$(TARGET)_cache
endif

#CXXFLAGS = -Wall -Wno-unknown-pragmas -Winline $(DBG) $(OPT) 
CXXFLAGS = -Wno-unknown-pragmas $(DBG) $(OPT) 
CXX = g++
CC  = gcc

VPATH = cacti
all: obj_$(TAG)/$(TARGET)
	cp -f obj_$(TAG)/$(TARGET) mcpat$(SUFFIX)

obj_$(TAG)/$(TARGET) : $(OBJS)
	$(CXX) $(OBJS) -o $@ $(INCS) $(CXXFLAGS) $(LIBS) -pthread

obj_$(TAG)/%.o : %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj_$(TAG)/%_cache.o : %.cc
	$(CXX) $(CXXFLAGS) -DENABLE_CACHE -c $< -o $@

clean:
	-rm -f *.o $(TARGET) $(TARGET)_CACHE $(TARGET)$(SUFFIX)
# $(info If a SUFFIX was provided at making, you need to provide it as well for cleanup)
