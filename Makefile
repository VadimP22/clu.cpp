# Makefile for Windows only

CC := clang++
LD := clang++

LLVM_MODULES = core

CXXFLAGS := $(shell llvm-config --cppflags)
CXXFLAGS += -std=c++20

LDFLAGS := $(shell llvm-config --ldflags)
LDFLAGS += -lntdll

LLVM_LIBS := $(shell llvm-config --libs $(LLVM_MODULES))
SYSTEM_LIBS := $(shell llvm-config --system-libs $(LLVM_MODULES))

all: clu.exe

debug:
	@echo $(CXXFLAGS)
	@echo ======
	@echo $(LDFLAGS)
	@echo ======
	@echo $(LLVM_LIBS)
	@echo ======
	@echo $(SYSTEM_LIBS)

clu.exe: clu.o
	$(LD) $(LDFLAGS) $(LLVM_LIBS) $^ -o $@

clu.o: clu.cpp
	$(CC) $(CXXFLAGS) -c $^ -o $@
	

clean:
	rm clu.o
	rm clue.exe
