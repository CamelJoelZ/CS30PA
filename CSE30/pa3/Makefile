#
# Makefile for CSE 30 -- PA3
# You should not need to change anything in this file.
#

HEADERS		= pa3.h pa3Strings.h test.h

C_SRCS		= main.c drawGraph.c generateGraph.c nameQuest.c printStats.c\
		  handleUserInput.c pa3Globals.c populateNameData.c\
		  parseCmd.c filenameCompare.c convertStr.c
ASM_SRCS	= hash.s getTableIndex.s isInRange.s myRemainder.s 

C_OBJS		= $(C_SRCS:.c=.o)
ASM_OBJS	= $(ASM_SRCS:.s=.o)
OBJS		= $(C_OBJS) $(ASM_OBJS)

EXE		= pa3
TEST_EXES	= testparseCmd testconvertStr testpopulateNameData\
		  testnameQuest testhash testgetTableIndex


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
	$(RM) -f test*.o test*.ln
	@echo "Linking all object modules ..."
	$(GCC) $(LD_FLAGS) -o $(EXE) $(OBJS)
	@echo ""
	@echo "Compilation Successful!"

$(C_OBJS): $(HEADERS)

clean:
	@echo "Cleaning up project directory ..."
	$(RM) -f $(EXE) $(TEST_EXES) *.o *.ln core a.out
	@echo ""
	@echo "Clean."

new:
	make clean
	make

#
# Unit test targets
#

# --- Test for parseCmd ---
testparseCmd: $(HEADERS) parseCmd.o testparseCmd.o
	@echo "Compiling testparseCmd.c"
	$(GCC) $(LD_FLAGS) -o testparseCmd testparseCmd.o parseCmd.o
	@echo "Compilation Successful!"

# --- Test for convertStr ---
testconvertStr: $(HEADERS) convertStr.o testconvertStr.o
	@echo "Compiling testconvertStr.c"
	$(GCC) $(LD_FLAGS) -o testconvertStr testconvertStr.o convertStr.o
	@echo "Compilation Successful!"

# --- Test for populateNameData ---
testpopulateNameData: $(HEADERS) populateNameData.o testpopulateNameData.o \
	filenameCompare.o convertStr.o getTableIndex.o nameQuest.o hash.o \
	pa3Globals.o myRemainder.o
	@echo "Compiling testpopulateNameData.c"
	$(GCC) $(LD_FLAGS) -o testpopulateNameData populateNameData.o \
	testpopulateNameData.o filenameCompare.o convertStr.o getTableIndex.o \
	nameQuest.o hash.o pa3Globals.o myRemainder.o
	@echo "Compilation Successful!"

# --- Test for nameQuest ---
testnameQuest: $(HEADERS) nameQuest.o testnameQuest.o
	@echo "Compiling testnameQuest.c"
	$(GCC) $(LD_FLAGS) -o testnameQuest testnameQuest.o nameQuest.o
	@echo "Compilation Successful!"

# --- Test for hash ---
testhash: $(HEADERS) hash.o testhash.o pa3Globals.o
	@echo "Compiling testhash.c"
	$(GCC) $(LD_FLAGS) -o testhash testhash.o hash.o pa3Globals.o
	@echo ""
	@echo "Compilation Successful!"

# --- Test for getTableIndex ---
testgetTableIndex: $(HEADERS) getTableIndex.o testgetTableIndex.o hash.o \
	pa3Globals.o myRemainder.o
	@echo "Compiling testgetTableIndex.c"
	$(GCC) $(LD_FLAGS) -o testgetTableIndex testgetTableIndex.o \
	getTableIndex.o hash.o pa3Globals.o myRemainder.o
	@echo ""
	@echo "Compilation Successful!"
