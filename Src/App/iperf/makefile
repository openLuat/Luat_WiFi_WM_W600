#/**************************************************************************
# * Kevin 2014-02-24                                                       *
# **************************************************************************/

#---------------------------------------------------------------------------
# Constant Variable definition
#---------------------------------------------------------------------------
ROOT = ../../..
include $(ROOT)/Tools/tool_chain.def
LIB_DIR =	$(ROOT)/lib/$(LIBDIR)

#---------------------------------------------------------------------------
# Target definition (User)
#---------------------------------------------------------------------------
GOAL  = $(LIB_DIR)/wmiperf.$(LIBTYPE)

#---------------------------------------------------------------------------
# Source section (User)
#---------------------------------------------------------------------------
ASM_SRC			+= 
C_SRC				+= iperf_api.c
C_SRC				+= iperf_client_api.c
C_SRC				+= iperf_error.c
C_SRC				+= iperf_main.c
C_SRC				+= iperf_net.c
C_SRC				+= iperf_server_api.c
C_SRC				+= iperf_tcp.c
C_SRC				+= iperf_udp.c
C_SRC				+= iperf_util.c
C_SRC				+= iperf_locale.c
C_SRC				+= tcp_info.c
C_SRC				+= tcp_window_size.c
C_SRC				+= iperf_timer.c
C_SRC				+= iperf_units.c
C_SRC				+= wm_perf.c

#---------------------------------------------------------------------------
# Implicit rules
#---------------------------------------------------------------------------
.c.o:
	@$(ECHO) "Compiling $<..."
	@$(CC) $(CCFLAGS) -c -o $*.o $< $(INCLUDE_DIR)

.s.o:
	@$(ECHO) "Compiling $<..."
	@$(ASM) $(ASMFLAGS) -c -o $*.o $< $(INCLUDE_DIR)

#---------------------------------------------------------------------------
# Explicit ruls
#---------------------------------------------------------------------------
OBJ_FILES	= $(C_SRC:%.c=%.o) $(ASM_SRC:%.s=%.o)

all: $(GOAL)

$(GOAL): $(OBJ_FILES)
	@$(AR) $(ARFLAGS) $@ $(OBJ_FILES)
	@$(ECHO) "***" $(GOAL) "is built successfully! ***"
	@$(ECHO) "---------"
	@rm -f $(OBJ_FILES:.o=.d) $(OBJ_FILES)
	
.PHONY: clean
clean:
	@rm -f $(GOAL)
	@rm -f $(OBJ_FILES:.o=.d) $(OBJ_FILES)
	