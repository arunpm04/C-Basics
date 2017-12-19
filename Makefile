#Makefile_Begin

VERBOSE = @
USER = $(shell whoami)
CWD=`pwd`
MACHINE_TYPE=`uname -m`

CC=gcc
CFLAGS=-Werror-unused-variables
LDFLAGS=

.PHONY: all cleanall

#==============================================================================
# Build all Applications
#==============================================================================
all: hexdump linkedlist

cleanall: clean_hexdump clean_linkedlist

#==============================================================================
hexdump:
	$(CC) -o hexdump $(CWD)/hexdump.c
clean_hexdump:
	$(RM) hexdump

linkedlist:
	$(CC) -o linkedlist $(CWD)/linked_list.c
clean_linkedlist:
	$(RM) linkedlist

# Makefile_End
