# Makefile for Windows only

CC := clang++
LD := clang++

SRC := $(wildcard *.cpp)
OBJ := $(SRC:%.cpp=%.o)

LLVM_MODULES = all

CXXFLAGS := $(shell llvm-config --cppflags)
CXXFLAGS += -std=c++20

LDFLAGS := $(shell llvm-config --ldflags)
LDFLAGS += -lntdll

LLVM_LIBS := $(shell llvm-config --libs $(LLVM_MODULES))
SYSTEM_LIBS := $(shell llvm-config --system-libs $(LLVM_MODULES))

all: clu.exe

clu.exe: $(OBJ)
	@echo LD $@
	@$(LD) $(LDFLAGS) $(LLVM_LIBS) $^ -o $@


%.o: %.cpp
	@echo CC $@
	@$(CC) $(CXXFLAGS) -c $^ -o $@
		
