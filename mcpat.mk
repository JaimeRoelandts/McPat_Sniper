TARGET = mcpat
SHELL = /bin/sh
.PHONY: all depend clean
.SUFFIXES: .cc .o

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
  OPT = -O3 -msse2 -mfpmath=sse -DNTHREADS=$(NTHREADS) -Icacti
  #OPT = -O0 -DNTHREADS=$(NTHREADS)
endif

# This allows to speed-up execution between runs of mcpat, by keeping intermediate results into a database. (This has nothing to do with CPU-caching.)
ifneq ($(CACHE),)
  OPT += -DENABLE_MEMOIZATION
  LIBS += -llmdb
else
  $(warning Results memoization is disabled by default. Please install lmdb and run make with CACHE=1.)
endif

#CXXFLAGS = -Wall -Wno-unknown-pragmas -Winline $(DBG) $(OPT) 
CXXFLAGS = -Wno-unknown-pragmas $(DBG) $(OPT) 
CXX = g++
CC  = gcc

VPATH = cacti

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
  powergating.cc \
  results_db.cc

OBJS = $(patsubst %.cc,obj_$(TAG)/%.o,$(SRCS))

all: obj_$(TAG)/$(TARGET)
	cp -f obj_$(TAG)/$(TARGET) $(TARGET)

obj_$(TAG)/$(TARGET) : $(OBJS)
	$(CXX) $(OBJS) -o $@ $(INCS) $(CXXFLAGS) $(LIBS) -pthread

#obj_$(TAG)/%.o : %.cc
#	$(CXX) -c $(CXXFLAGS) $(INCS) -o $@ $<

obj_$(TAG)/%.o : %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-rm -f *.o $(TARGET)
