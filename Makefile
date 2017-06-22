VFILE = Vtinyalu
SIM_TOP = sc_main

OUTPUT = out

TBFILES = $(wildcard *.h)

TBDIR = $(abspath tb/)
TBFILES = $(abspath $(wildcard $(TBDIR)/*h))
VMAKE = $(VFILE).mk
CFLAGS = -Wno-WIDTH
OUTPUT_FILES = $(wildcard $(OUTPUT)/*)
RTLFILES = $(wildcard rtl/*v)
EXEC = $(OUTPUT)/$(VFILE)
VCFLAGS = -CFLAGS -I/lib/uvm-systemc/include
VCFLAGS += -CFLAGS -I$(TBDIR)
DEBUG = 0
PREFIX =
COMPILE_DEBUG =

ifeq ($(DEBUG), 1)
	PREFIX = ddd
	COMPILE_DEBUG = -ggdb
	VCFLAGS += -CFLAGS $(COMPILE_DEBUG)
endif

build: $(EXEC)

run: $(EXEC)
	$(PREFIX) $(EXEC)

clean:
	rm -rf $(OUTPUT)

$(OUTPUT)/$(VMAKE): $(RTLFILES) 
	verilator $(CFLAGS) --sc $(RTLFILES) --Mdir $(OUTPUT) $(VCFLAGS) 

$(EXEC): $(OUTPUT)/$(VMAKE) $(SIM_TOP).cpp $(TBFILES)
	$(MAKE) -j -C $(OUTPUT) -f $(VMAKE) $(VFILE)__ALL.a
	$(MAKE) -j -C $(OUTPUT) -f $(VMAKE) $(SIM_TOP).o verilated.o
	g++ $(COMPILE_DEBUG) -I$(UVM_INCLUDE) -I$(SYSTEMC_INCLUDE) -L$(SYSTEMC_LIBDIR) -L$(UVM_LIBDIR) $(OUTPUT)/$(SIM_TOP).o $(OUTPUT)/verilated.o $(TBFILES) $(OUTPUT)/$(VFILE)__ALL*.o -o $(OUTPUT)/$(VFILE) -lsystemc -luvm-systemc
