#-------------------
# Variables
#------------------- 
CC         := g++ 
CFLAGS     := -std=c++14 -MP -MD -Wall
DEBUGFLAGS := -g -DDEBUGMODE=1
LIB_win    := -L lib/SFML-2.4.2-win/lib -lsfml-audio -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system -L lib/QuestiaEng-1.0.0-win -lquestia-eng.1.0.0 -L lib/Cryptopp-5.6.5-win -lcryptopp
LIB_win_db := -L lib/SFML-2.4.2-win/lib -lsfml-audio -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system -L lib/QuestiaEng-1.0.0-win -lquestia-eng-d.1.0.0 -L lib/Cryptopp-5.6.5-win -lcryptopp
LIB_lin    := -lcryptopp -lsfml-audio -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system -lquestia-eng.1.0.0
LIB_lin_db := -lcryptopp -lsfml-audio -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system -lquestia-eng-d.1.0.0
SRCEXT     := cpp

SRCDIR     := src
INC        := -I include
TARGET_R   := bin/QuestiaDev
TARGET_D   := bin/QuestiaDev_debug
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
	
	ifneq "$(findstring ebug, $(MAKECMDGOALS))" ""
		LIB := $(LIB_win_db)
	else
		LIB := $(LIB_win)
	endif
else
	SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))

	EXE = 
	
	ifneq "$(findstring ebug, $(MAKECMDGOALS))" ""
		LIB := $(LIB_lin_db)
	else
		LIB := $(LIB_lin)
	endif
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