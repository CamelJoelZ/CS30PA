#
# Makefile template for CSE 30 -- Debug 2
# You should not need to change anything in this file.
#

HEADERS		= debug2.h debug2Strings.h
C_SRCS		= freqs.c handleUserInput.c parseFile.c parseCmd.c bsearchd.c debug2Globals.c
ASM_SRCS	= compareFreqWord.s accumulateWordCount.s

C_OBJS		= $(C_SRCS:.c=.o)
ASM_OBJS	= $(ASM_SRCS:.s=.o)
OBJS		= $(C_OBJS) $(ASM_OBJS)

EXE		= freqs

GCC		= /usr/bin/gcc
ASM		= $(GCC)
RM		= rm

GCC_FLAGS	= -c -g -W -Wall -D__EXTENSIONS__ -std=c99
ASM_FLAGS	= -c -g
LD_FLAGS	= -g -Wall


#
# Standard rules
#

.s.o:
	@echo "Assembling each assembly source file separately ..."
	$(ASM) $(ASM_FLAGS) $<
	@echo ""

.c.o:
	@echo "Compiling each C source file separately ..."
	$(GCC) $(GCC_FLAGS) $<
	@echo ""

#
# Have our project target be named whatever we specify above for EXE.
#

$(EXE):	$(OBJS)
	@echo "Linking all object modules ..."
	$(GCC) $(LD_FLAGS) -o $(EXE) $(OBJS)
	@echo ""
	@echo "Compilation Successful!"

$(C_OBJS): $(HEADERS)

clean:
	@echo "Cleaning up project directory ..."
	$(RM) -f $(OBJS) $(EXE) core
	@echo ""
	@echo "Clean."

new:
	make clean
	make
