# project name (generate executable with this name)
TARGET   = maximum_subarray

CC       = gcc
# compiling flags here
CFLAGS   = -std=c89 -Wall -g -Werror -pedantic
LIBFLAGS = 
LINKER   = gcc -o
# linking flags here
LFLAGS   = -std=c89 -Wall -g -Werror -pedantic

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm        = rm -f

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS) $(LIBFLAGS)
	@echo "Linking complete"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)

.PHONY: cleanall
cleanall: clean remove
