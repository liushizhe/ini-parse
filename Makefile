# change 'rm' to 'del' if you have no Fileutils

CC = gcc
AR = ar
RM = rm
EXE = ini_parse
LBIN = bin
LOBJ = obj
LSRC = src
CDEBUG      = 
CFLAGS      = $(CDEBUG) -g -Wall #-Wextra -O2
LIBS        = -lncurses
INCLUDESDIR =
LIBSDIR     =
DEFINES =
OBJ = obj/ini_parse.o obj/main.o

# Verbose mode check
ifdef V
MUTE =
VTAG = -v
else
MUTE = @
endif

ifdef DEBUG
CDEBUG = -D_XX
else
CDEBUG =
endif

#############################################################################
# Make targets
all: dirs $(EXE)
	@echo "* Build successful!"

$(EXE): $(OBJ) 
	@echo "* Linking..."
	$(MUTE)$(CC) $(OBJ) -o $(LBIN)/$(EXE) $(LIBSDIR) $(LIBS)

$(LOBJ)/%.o: $(LSRC)/%.c
	@echo "* Compiling $<..."
	$(MUTE)$(CC) $(CFLAGS) $(CDEBUG) $< -c -o $@ $(DEFINES) $(INCLUDESDIR)

# Phony targets
dirs:
	@-mkdir -p $(LOBJ) $(LBIN)

clean:
	@echo "* Cleaning files..."
	$(MUTE)$(RM) $(VTAG) -f $(LOBJ)/*.o
	$(MUTE)$(RM) $(VTAG) -f $(LBIN)/*

.PHONY: clean dirs
