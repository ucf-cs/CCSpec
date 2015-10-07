# A few common Makefile items

CC = gcc
CXX = g++ -std=c++11

UNAME = $(shell uname)

LIB_NAME = model
LIB_SO = lib$(LIB_NAME).so

BASE = ../..
INCLUDE = -I$(BASE)/include -I../include -I$(BASE) -I..

# C preprocessor flags
CPPFLAGS += $(INCLUDE) -g

# C++ compiler flags
CXXFLAGS += $(CPPFLAGS)

# C compiler flags
CFLAGS += $(CPPFLAGS)

# Linker flags
LDFLAGS += -L$(BASE) -l$(LIB_NAME) -rdynamic

# Mac OSX options
ifeq ($(UNAME), Darwin)
MACFLAGS = -D_XOPEN_SOURCE -DMAC
CPPFLAGS += $(MACFLAGS)
CXXFLAGS += $(MACFLAGS)
CFLAGS += $(MACFLAGS)
LDFLAGS += $(MACFLAGS)
endif
