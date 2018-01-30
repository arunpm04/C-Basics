#Makefile_Begin

VERBOSE=@
USER=$(shell whoami)
CWD=$(shell pwd)
MACHINE_TYPE=$(shell uname -m)

CC=gcc
CFLAGS=-Werror=unused-variable -I. -DAPP_DEBUG_EN=1
LDFLAGS=

.PHONY: all hexdump linkedlist statemachine clean clean_hexdump clean_linkedlist clean_statemachine

#==============================================================================
# Build all Applications
#==============================================================================
all: hexdump linkedlist statemachine

clean: clean_hexdump clean_linkedlist clean_statemachine

#==============================================================================
hexdump:
	$(CC) $(CFLAGS) $(LDFLAGS) -o hexdump $(CWD)/hexdump.c
clean_hexdump:
	$(RM) hexdump

linkedlist:
	$(CC) $(CFLAGS) $(LDFLAGS) -o linkedlist $(CWD)/linked_list.c
clean_linkedlist:
	$(RM) linkedlist

statemachine:
	$(CC) $(CFLAGS) $(LDFLAGS) -o statemachine $(CWD)/simple_state_machine.c
clean_statemachine:
	$(RM) statemachine

# Makefile_End
