#Makefile_Begin

VERBOSE=@
USER=$(shell whoami)
CWD=$(shell pwd)
MACHINE_TYPE=$(shell uname -m)

CC=gcc
CFLAGS=-Werror=unused-variable -I. -DAPP_DEBUG_EN=1
LDFLAGS=

.PHONY: all hexdump linkedlist clean clean_hexdump clean_linkedlist

#==============================================================================
# Build all Applications
#==============================================================================
all: hexdump linkedlist

clean: clean_hexdump clean_linkedlist

#==============================================================================
hexdump:
	$(CC) $(CFLAGS) $(LDFLAGS) -o hexdump $(CWD)/hexdump.c
clean_hexdump:
	$(RM) hexdump

linkedlist:
	$(CC) $(CFLAGS) $(LDFLAGS) -o linkedlist $(CWD)/linked_list.c
clean_linkedlist:
	$(RM) linkedlist

# Makefile_End
