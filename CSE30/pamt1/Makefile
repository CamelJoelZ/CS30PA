#
# Makefile template for CSE 30 -- PAMT1
#

HEADERS		= pamt1.h

C_SRCS		= initData.c squaredSumMinMax.c main.c \
		  parallel_initData.c parallel_squaredSumMinMax.c \
	          sqrtSumMinMax.c parallel_sqrtSumMinMax.c

C_OBJS		= initData.o squaredSumMinMax.o main.o \
		  parallel_initData.o parallel_squaredSumMinMax.o \
	          sqrtSumMinMax.o parallel_sqrtSumMinMax.o

OBJS		= ${C_OBJS}

EXE		= pamt1

#
# Relevant man pages:
#
# man gcc
#

GCC		= gcc

GCC_FLAGS	= -c -Wall -std=c99 -fopenmp
LD_FLAGS	= -lm -fopenmp

#
# Standard rules
#

.c.o:
	@echo "Compiling each C source file separately ..."
	$(GCC) $(GCC_FLAGS) $<
	@echo ""

#
# Simply have our project target be a single default $(EXE) executable.
#

$(EXE):	$(OBJS)
	@echo "Linking all object modules ..."
	$(GCC) -o $(EXE) $(LD_FLAGS) $(OBJS)
	@echo ""
	@echo "Done."

${C_OBJS}:      ${HEADERS}

clean:
	@echo "Cleaning up project directory ..."
	rm -f *.o $(EXE) *.ln core a.out
	@echo ""
	@echo "Clean."

new:
	make clean
	make

