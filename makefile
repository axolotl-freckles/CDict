CPP  = cl
LINK = link
VERSION = 0.0

SRC_DIR   = ./src
BIN_DIR   = ./bin
BUILD_DIR = ./build
INC_DIR   = $(SRC_DIR)/inc
DEBUG_TAR = /debug
RELEA_TAR = /release

COMP_FLAGS = /Wall /EHsc /nologo /std:c++20 /I$(INC_DIR)
DEB_FLAGS  = /Od /Zi
REL_FLAGS  = /O2 /Zo

LINK_FLAGS = /nologo /version:$(VERSION) /debug

debug: $(BIN_DIR)$(DEBUG_TAR)/cdict.exe

$(BIN_DIR)$(DEBUG_TAR)/cdict.exe: $(BUILD_DIR)$(DEBUG_TAR)/main.obj
	$(LINK) $(LINK_FLAGS) $** /OUT:$@

{$(SRC_DIR)/}.cpp{$(BUILD_DIR)$(DEBUG_TAR)/}.obj:
	$(CPP) "$<" /c $(COMP_FLAGS) $(DEB_FLAGS) /Fo"$@"
