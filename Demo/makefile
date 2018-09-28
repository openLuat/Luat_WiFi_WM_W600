#/**************************************************************************
# * Kevin 2014-02-24                                                       *
# **************************************************************************/

#---------------------------------------------------------------------------
# Constant Variable definition
#---------------------------------------------------------------------------
ROOT = ..
include $(ROOT)/Tools/tool_chain.def
LIB_DIR =	$(ROOT)/lib/$(LIBDIR)

#---------------------------------------------------------------------------
# Target definition (User)
#---------------------------------------------------------------------------
GOAL  = $(LIB_DIR)/wmdemo.$(LIBTYPE)

#---------------------------------------------------------------------------
# Source section (User)
#---------------------------------------------------------------------------
ASM_SRC			+= 
      
C_SRC				+= wm_crypt_demo.c 
C_SRC				+= wm_mcast_demo.c  
C_SRC				+= wm_raw_socket_server_demo.c        
C_SRC				+= wm_socket_client_demo.c    
C_SRC				+= wm_socket_fwup.c           
C_SRC				+= wm_socket_fwup_demo.c      
C_SRC				+= wm_socket_server_demo.c    
C_SRC				+= wm_socket_server_sel_demo.c
C_SRC				+= wm_softap_demo.c
             
C_SRC				+= wm_http_fwup.c 
C_SRC				+= wm_i2c_demo.c
C_SRC				+= wm_adc_demo.c
C_SRC				+= wm_7816_demo.c
C_SRC				+= wm_uart_demo.c
C_SRC				+= ./console/wm_demo_console_task.c
C_SRC				+= wm_gpio_demo.c
C_SRC				+= wm_flash_demo.c
C_SRC				+= wm_pwm_demo.c
C_SRC				+= wm_slave_spi_demo.c
C_SRC				+= wm_master_spi_demo.c 
C_SRC				+= wm_rtc_demo.c 
C_SRC				+= wm_timer_demo.c 
C_SRC				+= wm_pmu_demo.c 
C_SRC				+= wm_crypt_hard_demo.c 
C_SRC				+= wm_rsa_demo.c 
C_SRC				+= wm_raw_socket_client_demo.c
C_SRC				+= wm_connect_net_demo.c
C_SRC				+= wm_http_demo.c  
#C_SRC				+= wm_ntp_demo.c
#C_SRC				+= wm_dlna_dmr_demo.c
#C_SRC				+= wm_spi_codec_demo.c 
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
	
