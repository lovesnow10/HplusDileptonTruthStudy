GCC = g++
ROOTFLAGS := $(shell root-config --cflags)
ROOTLIBS := $(shell root-config --libs)
SRCDIR = src
INCDIR = include
SOURCEFILES = $(wildcard $(SRCDIR)/*.C)
OBJS = $(patsubst %.C, %.o, $(SOURCEFILES))

CFLAGS += $(ROOTFLAGS)
CFLAGS += -I$(INCDIR)
LIBS += $(ROOTLIBS)

all: CheckEff
# .PHONY: all

%.o: %.C
	$(GCC) $(CFLAGS) -c -g -o $@ $<

% : utils/%.o $(OBJS)
	echo $@
	$(GCC) $(CFLAGS) -o $@ $(patsubst %, %.o, utils/$@) $(OBJS) $(LIBS)
