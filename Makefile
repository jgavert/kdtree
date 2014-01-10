DIRS := src
PROGRAM_DIRS := $(DIRS)

INCLUDE_DIRS :=
WARNINGS := -pedantic -Wall -Wextra -Wno-parentheses

PACKAGES :=
YASM     := yasm
YASMFLAGS:= -f elf64
CXX      := clang++
CXXFLAGS := $(WARNINGS) -std=c++11 -pthread -O0 $(INCLUDE_DIRS)
#CXXFLAGS += $(shell pkg-config --cflags $(PACKAGES))

LIBS := -pthread
#LIBS += $(shell pkg-config --libs $(PACKAGES))

PROGRAM = bin/main

SRC := src
OBJ := obj
BIN := bin

all: dirs $(PROGRAM)

debug: CXXFLAGS += -O0 -g
debug: LIBS += -g
debug: all

prof: CXXFLAGS += -pg
prof: LIBS += -pg
prof: all

SRC_PROGRAM := $(foreach dir, $(PROGRAM_DIRS), $(wildcard $(dir)/*.cc))
ASMSRC_PROGRAM := $(foreach dir, $(PROGRAM_DIRS), $(wildcard $(dir)/*.asm))

OBJ_PROGRAM := $(patsubst $(SRC)/%.cc, $(OBJ)/%.o, $(SRC_PROGRAM))
ASMOBJ_PROGRAM := $(patsubst $(SRC)/%.asm, $(OBJ)/%.o, $(ASMSRC_PROGRAM))

DEPFILES := $(OBJ_PROGRAM:.o=.d)
DEPFILES := $(sort $(DEPFILES))

.PHONY: all clean dirs echo

all: dirs $(PROGRAM)

$(PROGRAM): $(OBJ_PROGRAM) $(ASMOBJ_PROGRAM)

$(BIN)/%:
	@echo LINK $@
	@$(CXX) $^ $(LIBS) -o $@

$(OBJ)/%.o: $(SRC)/%.cc
	@echo CXX $@
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@$(CXX) $(CXXFLAGS) -MM -MT "$(@:.d=.o) $@" $< > $(@:.o=.d)

$(OBJ)/%.o: $(SRC)/%.asm
	@echo YASM $@
	@$(YASM) $(YASMFLAGS) $< -o $@

clean:
	@$(RM) -rf $(PROGRAM) $(OBJ)

dirs:
	@mkdir -p $(BIN)
	@mkdir -p $(OBJ)
	@mkdir -p $(patsubst $(SRC)/%, $(OBJ)/%, $(shell find $(PROGRAM_DIRS) -type d))

ifneq ($(MAKECMDGOALS),clean)
  -include $(DEPFILES)
endif

