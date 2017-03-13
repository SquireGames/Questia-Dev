#-------------------
# Variables
#------------------- 
CC         := g++ 
CFLAGS     := -std=c++11 -MP -MD
DEBUGFLAGS := -g -DDEBUGMODE=1
LIB_win    := -L lib/SFML-2.4.2-win/lib -lsfml-audio -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system -L lib/QuestiaEng-1.0.0-win -lquestia-eng.1.0.0
LIB_lin    := -L lib/SFML-2.4.2-lin/lib -lsfml-audio -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system
SRCEXT     := cpp

SRCDIR     := src
INC        := -I include
TARGET_R   := bin/Questia
TARGET_D   := bin/Questia_debug
BUILDDIR_R := build
BUILDDIR_D := build_debug

#-------------------
# Mode
#-------------------

ifneq "$(findstring ebug, $(MAKECMDGOALS))" ""
	TARGET   := $(TARGET_D)
	BUILDDIR := $(BUILDDIR_D)
	CFLAGS   += $(DEBUGFLAGS)
else
	TARGET   := $(TARGET_R)
	BUILDDIR := $(BUILDDIR_R)
endif

#-------------------
# Dependant Variables
#-------------------

ifeq ($(OS),Windows_NT)
	SOURCES := $(wildcard src/*.$(SRCEXT)) $(wildcard src/**/*.$(SRCEXT)) $(wildcard src/**/**/*.$(SRCEXT))\
	$(wildcard src/**/**/**/*.$(SRCEXT)) $(wildcard src/**/**/**/**/*.$(SRCEXT))\
	$(wildcard src/**/**/**/**/**/*.$(SRCEXT)) $(wildcard src/**/**/**/**/**/**/*.$(SRCEXT))
	
	EXE := .exe
	LIB := $(LIB_win)
else
	SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))

	EXE = 
	LIB := $(LIB_lin)
endif

OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS := $(OBJECTS:.o=.d))

#------------------- 
# Build
#-------------------

all: default
default: release
Release: release
Debug: release
debug: release

release: $(OBJECTS) $(TARGET)$(EXE)

$(TARGET)$(EXE): $(OBJECTS)
ifeq ($(OS),Windows_NT)
	cmd /c if not exist $(subst /,\\, $(dir $@)) md $(subst /,\\, $(dir $@))
else
	mkdir -p $(dir $@)
endif
	echo " Linking..."
	$(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
ifeq ($(OS),Windows_NT)
	cmd /c if not exist $(subst /,\\, $(dir $@)) md $(subst /,\\, $(dir $@))
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
else
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
endif

clean: cleanRelease cleanDebug

cleanRelease:
	@echo " Cleaning Release...";
ifeq ($(OS),Windows_NT)
	-cmd /c rmdir /s /q $(BUILDDIR_R)
	-cmd /c del /f $(subst /,\\,$(TARGET_R)).exe
else
	$(RM) -r $(BUILDDIR_R) $(TARGET_R)
endif

cleanDebug:
	@echo " Cleaning Debug...";
ifeq ($(OS),Windows_NT)
	-cmd /c rmdir /s /q $(BUILDDIR_D)
	-cmd /c del /f $(subst /,\\,$(TARGET_D)).exe
else
	$(RM) -r $(BUILDDIR_D) $(TARGET_D)
endif

.PHONY: clean
#------------ 
-include $(DEPS)
