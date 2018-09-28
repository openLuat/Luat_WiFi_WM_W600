#/**************************************************************************
# * Kevin 2014-02-24                                                       *
# **************************************************************************/

#---------------------------------------------------------------------------
# Constant Variable definition
#---------------------------------------------------------------------------
ROOT = ../../..
include $(ROOT)/Tools/tool_chain.def 
LIB_DIR =	$(ROOT)/lib

#---------------------------------------------------------------------------
# Target definition (User)
#---------------------------------------------------------------------------
GOAL  = $(LIB_DIR)/wmboot.$(LIBTYPE)

#---------------------------------------------------------------------------
# Source section (User)
#---------------------------------------------------------------------------
ifeq ($(ARCH_M3),1)
ASM_SRC  += startup_venus.s
C_SRC		 += misc.c
C_SRC		 += retarget.c
endif

ifeq ($(ARCH_M3),0)
ASM_SRC		+= start.s
ASM_SRC		+= mpu.s
C_SRC			+= retarget.c
endif

#---------------------------------------------------------------------------
# Linker options
#---------------------------------------------------------------------------
ifeq ($(ARCH_M3),1)
LDFLAGS	   += --cpu Cortex-M3 --li
LDFLAGS    += --strict
LDFLAGS	   += --summary_stderr 
LDFLAGS    += --xref 
LDFLAGS    += --callgraph 
LDFLAGS	   += --partial 
endif
ifeq ($(ARCH_M3),0)
LDFLAGS	   += --cpu ARM966E-S
LDFLAGS    += --strict
LDFLAGS	   += --summary_stderr 
LDFLAGS    += --xref 
LDFLAGS    += --callgraph 
LDFLAGS	   += --partial 
endif

#---------------------------------------------------------------------------
# Implicit rules
#---------------------------------------------------------------------------
.c.o:
	@$(ECHO) "Compiling $<..."
	@$(CC) $(CCFLAGS) -c -o $*.o $< $(INCLUDE_DIR)

.s.o:
	@$(ECHO) "Compiling $<..."
	@$(ASM) $(ASMFLAGS) -o $*.o $< $(INCLUDE_DIR)

#---------------------------------------------------------------------------
# Explicit ruls
#---------------------------------------------------------------------------
OBJ_FILES	= $(C_SRC:%.c=%.o) $(ASM_SRC:%.s=%.o)

all:$(GOAL)

$(GOAL) : $(OBJ_FILES)
	@$(LD) $(OBJ_FILES) $(LDFLAGS) --output $@
	@$(ECHO) "***" $(GOAL) "is built successfully! ***"
	@rm -f $(OBJ_FILES:.o=.d) $(OBJ_FILES)

clean:
	@rm -f $(OBJ_FILES:.o=.d) $(OBJ_FILES) $(GOAL).*
