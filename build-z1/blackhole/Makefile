CONTIKI_PROJECT = blackhole-attack
all: $(CONTIKI_PROJECT)

CONTIKI = ../../../..
CONTIKI_TARGET = z1

MODULES += os/net/ipv6
MODULES += os/net/rpl

# Compile the correct source file
PROJECT_SOURCEFILES += blackhole-attack.c

include $(CONTIKI)/Makefile.include

