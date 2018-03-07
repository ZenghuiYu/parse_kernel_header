CXX ?= gcc

all:            parse_header
parse_header: common.h linux.h parse_header.c; $(CXX) $^ -o $@ -Wall

clean: ; rm -f parse_header
