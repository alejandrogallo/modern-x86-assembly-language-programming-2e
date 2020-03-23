ASFLAGS  ?= --64
CPPFLAGS ?= -m64 -g -O0 -pedantic -Wall --all-warnings
LDFLAGS  ?=

OBJS = $(patsubst %.asm,%.o,$(wildcard *.asm)) \
       $(patsubst %.cpp,%.o,$(wildcard *.cpp)) \
       $(patsubst %.c,%.o,$(wildcard *.c)) \

TARGETS = $(OBJS) main

main: $(OBJS)
	g++ $(LDFLAGS) $(OBJS) -o $@

main.lst: main
	objdump -Mintel -d $< > $@

diss: main.lst

%.o: %.asm
	as ${ASFLAGS} $< -o $@

clean:
	for i in $(wildcard $(TARGETS)); do rm -v $$i; done
	
.PHONY: clean diss
