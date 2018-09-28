#/**************************************************************************
# * Kevin 2014-02-24                                                       *
# **************************************************************************/

#---------------------------------------------------------------------------
# Constant Variable definition
#---------------------------------------------------------------------------
ROOT = ../..
include $(ROOT)/Tools/tool_chain.def
LIB_DIR =	$(ROOT)/lib/$(LIBDIR)

#---------------------------------------------------------------------------
# Target definition (User)
#---------------------------------------------------------------------------
GOAL  = $(LIB_DIR)/wmlwip.$(LIBTYPE)

#---------------------------------------------------------------------------
# Source section (User)
#---------------------------------------------------------------------------
ASM_SRC			+= 
ifeq ($(LWIP_141), 1)
C_SRC				+= lwip1.4.1/ethernet.c
C_SRC				+= lwip1.4.1/sys_arch.c

C_SRC				+= lwip1.4.1/api/api_lib.c
C_SRC				+= lwip1.4.1/api/api_msg.c
C_SRC				+= lwip1.4.1/api/err.c
C_SRC				+= lwip1.4.1/api/netbuf.c
C_SRC				+= lwip1.4.1/api/netdb.c
C_SRC				+= lwip1.4.1/api/netifapi.c
C_SRC				+= lwip1.4.1/api/sockets.c
C_SRC				+= lwip1.4.1/api/tcpip.c

C_SRC				+= lwip1.4.1/netif/etharp.c
C_SRC				+= lwip1.4.1/netif/ethernetif.c

C_SRC				+= lwip1.4.1/core/tcp.c
C_SRC				+= lwip1.4.1/core/tcp_in.c
C_SRC				+= lwip1.4.1/core/tcp_out.c
C_SRC				+= lwip1.4.1/core/timers.c
C_SRC				+= lwip1.4.1/core/udp.c
C_SRC				+= lwip1.4.1/core/def.c
C_SRC				+= lwip1.4.1/core/dhcp.c
C_SRC				+= lwip1.4.1/core/dns.c
C_SRC				+= lwip1.4.1/core/init.c
C_SRC				+= lwip1.4.1/core/mem.c
C_SRC				+= lwip1.4.1/core/memp.c
C_SRC				+= lwip1.4.1/core/netif.c
C_SRC				+= lwip1.4.1/core/pbuf.c
C_SRC				+= lwip1.4.1/core/raw.c
C_SRC				+= lwip1.4.1/core/stats.c
C_SRC				+= lwip1.4.1/core/sys.c
C_SRC				+= lwip1.4.1/core/alg.c

C_SRC				+= lwip1.4.1/core/ipv4/autoip.c
C_SRC				+= lwip1.4.1/core/ipv4/icmp.c
C_SRC				+= lwip1.4.1/core/ipv4/igmp.c
C_SRC				+= lwip1.4.1/core/ipv4/inet.c
C_SRC				+= lwip1.4.1/core/ipv4/inet_chksum.c
C_SRC				+= lwip1.4.1/core/ipv4/ip.c
C_SRC				+= lwip1.4.1/core/ipv4/ip_addr.c
C_SRC				+= lwip1.4.1/core/ipv4/ip_frag.c

C_SRC				+= api/tls_netconn.c
C_SRC				+= api/tls_sockets.c
else
C_SRC				+= api2.0.3/tls_sockets.c
C_SRC				+= api2.0.3/tls_netconn.c
C_SRC				+= lwip2.0.3/core/dns.c
C_SRC				+= lwip2.0.3/core/def.c
C_SRC				+= lwip2.0.3/core/init.c
C_SRC				+= lwip2.0.3/core/mem.c
C_SRC				+= lwip2.0.3/core/memp.c
C_SRC				+= lwip2.0.3/core/netif.c
C_SRC				+= lwip2.0.3/core/pbuf.c
C_SRC				+= lwip2.0.3/core/raw.c
C_SRC				+= lwip2.0.3/core/stats.c
C_SRC				+= lwip2.0.3/core/sys.c
C_SRC				+= lwip2.0.3/core/tcp.c
C_SRC				+= lwip2.0.3/core/tcp_in.c
C_SRC				+= lwip2.0.3/core/tcp_out.c
C_SRC				+= lwip2.0.3/core/udp.c
C_SRC				+= lwip2.0.3/core/inet_chksum.c
C_SRC				+= lwip2.0.3/core/ip.c
C_SRC				+= lwip2.0.3/core/timeouts.c
C_SRC				+= lwip2.0.3/core/alg.c
C_SRC				+= lwip2.0.3/core/ipv4/ip4_frag.c
C_SRC				+= lwip2.0.3/core/ipv4/ip4_addr.c
C_SRC				+= lwip2.0.3/core/ipv4/ip4.c
C_SRC				+= lwip2.0.3/core/ipv4/dhcp.c
C_SRC				+= lwip2.0.3/core/ipv4/etharp.c
C_SRC				+= lwip2.0.3/core/ipv4/igmp.c
C_SRC				+= lwip2.0.3/core/ipv4/icmp.c
C_SRC				+= lwip2.0.3/core/ipv4/autoip.c
C_SRC				+= lwip2.0.3/core/ipv6/ip6_frag.c
C_SRC				+= lwip2.0.3/core/ipv6/ip6_addr.c
C_SRC				+= lwip2.0.3/core/ipv6/ip6.c
C_SRC				+= lwip2.0.3/core/ipv6/dhcp6.c
C_SRC				+= lwip2.0.3/core/ipv6/ethip6.c
C_SRC				+= lwip2.0.3/core/ipv6/icmp6.c
C_SRC				+= lwip2.0.3/core/ipv6/inet6.c
C_SRC				+= lwip2.0.3/core/ipv6/mld6.c
C_SRC				+= lwip2.0.3/core/ipv6/nd6.c
C_SRC				+= lwip2.0.3/sys_arch.c
C_SRC				+= lwip2.0.3/netif/ethernetif.c
C_SRC				+= lwip2.0.3/netif/ethernet.c
C_SRC				+= lwip2.0.3/netif/wm_ethernet.c
C_SRC				+= lwip2.0.3/api/tcpip.c
C_SRC				+= lwip2.0.3/api/api_lib.c
C_SRC				+= lwip2.0.3/api/api_msg.c
C_SRC				+= lwip2.0.3/api/err.c
C_SRC				+= lwip2.0.3/api/netbuf.c
C_SRC				+= lwip2.0.3/api/netdb.c
C_SRC				+= lwip2.0.3/api/netifapi.c
C_SRC				+= lwip2.0.3/api/sockets.c
endif
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
	