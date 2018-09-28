#/**************************************************************************
# * Kevin 2014-02-24                                                       *
# **************************************************************************/

#---------------------------------------------------------------------------
# Constant Variable definition
#---------------------------------------------------------------------------
ROOT = ../..
include $(ROOT)/Tools/tool_chain.def
LIB_DIR =	$(ROOT)/Lib/$(LIBDIR)


#---------------------------------------------------------------------------
# Target definition (User)
#---------------------------------------------------------------------------
GOAL  = $(LIB_DIR)/wmdriver.$(LIBTYPE)

#---------------------------------------------------------------------------
# Source section (User)
#---------------------------------------------------------------------------

#---------------------------------------------------------------------------
# Link Library Section
#---------------------------------------------------------------------------
ASM_SRC			+= 
C_SRC				+= adc/wm_adc.c
C_SRC				+= cpu/wm_cpu.c
C_SRC				+= dma/wm_dma.c
C_SRC				+= efuse/wm_efuse.c
C_SRC				+= flash/wm_fls.c
C_SRC				+= flash/wm_fls_gd25qxx.c
C_SRC				+= gpio/wm_gpio.c
C_SRC				+= gpio/wm_gpio_afsel.c
C_SRC				+= hspi/wm_hspi.c
C_SRC				+= i2c/wm_i2c.c
C_SRC				+= irq/wm_irq.c
C_SRC				+= pwm/wm_pwm.c
C_SRC				+= rtc/wm_rtc.c
C_SRC				+= spi/wm_hostspi.c
C_SRC				+= timer/wm_timer.c
C_SRC				+= uart/wm_uart.c
C_SRC				+= watchdog/wm_watchdog.c
#special for venus
ifeq ($(ARCH_M3),1)
C_SRC				+= internalflash/wm_internal_fls.c
C_SRC				+= i2s/wm_i2s.c
C_SRC				+= io/wm_io.c
C_SRC				+= lcd/wm_lcd.c
C_SRC				+= 7816/wm_7816.c
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

all: $(GOAL)

$(GOAL): $(OBJ_FILES) $(LIB_SRC)
ifeq ($(TOOL_GNU),1)
		@$(AR) $(ARFLAGS) $@ $(OBJ_FILES)
else
		@$(AR) --create $@ $(OBJ_FILES) $(LIB_SRC)
endif
	@$(ECHO) "***" $(GOAL) "is built successfully! ***"
	@$(ECHO) "---------"
	@rm -f $(OBJ_FILES:.o=.d) $(OBJ_FILES)

.PHONY: clean
clean:
	@rm -f $(GOAL)
	@rm -f $(OBJ_FILES:.o=.d) $(OBJ_FILES)
	

