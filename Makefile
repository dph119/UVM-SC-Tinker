VFILE = Vtinyalu
SIM_TOP = sc_main

CWD = $(abspath .)

OUTPUT = out
OUTPUT_ABS = $(abspath $(OUTPUT))

TBFILES = $(wildcard *.h)
TBDIR = $(abspath tb/)
TBFILES = $(abspath $(wildcard $(TBDIR)/*h))

VMAKE = $(VFILE).mk
CFLAGS = -Wno-WIDTH
OUTPUT_FILES = $(wildcard $(OUTPUT)/*)
RTLFILES = $(wildcard rtl/*v)
EXEC = $(OUTPUT)/$(VFILE)
VCFLAGS = -CFLAGS -I$(UVM_INCLUDE)
VCFLAGS += -CFLAGS -I$(TBDIR)
VCFLAGS += -CFLAGS -I$(CWD)
VCFLAGS += -CFLAGS -L$(SYSTEMC_LIBDIR)
VCFLAGS += -CFLAGS -I$(SYSTEMC_INCLUDE)
VCFLAGS += -CFLAGS -lsystemc
DEBUG = 0
PREFIX =
COMPILE_DEBUG =
VOPTS =
WAVE =

ifeq ($(DEBUG), 1)
	PREFIX = ddd
	COMPILE_DEBUG = -ggdb
	VCFLAGS += -CFLAGS $(COMPILE_DEBUG)
endif

ifeq ($(WAVE), 1)
	VOPTS += --trace
	WAVE_CPP = $(VERILATOR_ROOT)/include/verilated_vcd_c.cpp $(VERILATOR_ROOT)/include/verilated_vcd_sc.cpp
endif

$(EXEC): $(OUTPUT)/$(VMAKE) $(SIM_TOP).cpp $(TBFILES) 
	$(MAKE) -j -C $(OUTPUT) -f $(VMAKE) $(VFILE)__ALL.a
	$(MAKE) -j -C $(OUTPUT) -f $(VMAKE) $(SIM_TOP).o verilated.o 
	g++ $(COMPILE_DEBUG) -I$(OUTPUT_ABS) $(WAVE_CPP) -I$(UVM_INCLUDE) -I$(VERILATOR_INCLUDE) -I$(SYSTEMC_INCLUDE) -L$(SYSTEMC_LIBDIR) -L$(UVM_LIBDIR) $(OUTPUT)/$(SIM_TOP).o $(OUTPUT)/verilated.o $(TBFILES) $(OUTPUT)/$(VFILE)__ALL*.o -o $(OUTPUT)/$(VFILE) -lsystemc -luvm-systemc

$(OUTPUT)/$(VMAKE): $(RTLFILES)
	verilator $(CFLAGS) --sc $(RTLFILES) --Mdir $(OUTPUT) $(VCFLAGS) $(VOPTS) --clk clk

run: $(EXEC)
	$(PREFIX) $(EXEC)

clean:
	rm -rf $(OUTPUT)
