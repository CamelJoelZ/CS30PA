#
# Makefile for CSE 30 -- Debug1
# You should not need to change anything in this file.
#

HEADERS		= debug1.h debug1Strings.h
C_SRCS		= main.c vigenereDec.c xorDec.c getKeyByte.c debug1Globals.c
ASM_SRCS	= vigenereEnc.s xorEnc.s myRand.s isInRange.s

C_OBJS		= $(C_SRCS:.c=.o)
ASM_OBJS	= $(ASM_SRCS:.s=.o)
OBJS		= $(C_OBJS) $(ASM_OBJS)

EXE		= crypt

GCC		= gcc
ASM		= $(GCC)
RM		= rm

GCC_FLAGS	= -c -g -std=c99 -pedantic -Wall -D__EXTENSIONS__
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
# Simply have our project target be a single default $(EXE) executable.
#

$(EXE):	$(OBJS)
	@echo "Linking all object modules ..."
	$(GCC) $(LD_FLAGS) -o $(EXE) $(OBJS)
	@echo ""
	@echo "Compilation Successful!"

$(C_OBJS): $(HEADERS)

clean:
	@echo "Cleaning up project directory ..."
	$(RM) -f $(EXE) *.o core a.out
	@echo ""
	@echo "Clean."

new:
	make clean
	make
