VFILE = Vtinyalu
CFILES = $(wildcard *h)
VMAKE = $(VFILE).mk
CFLAGS = -Wno-WIDTH
VERILATOR_OUT = out
VERILATOR_OUT_FILES = $(wildcard $(VERILATOR_OUT)/*)
RTLFILES = $(wildcard rtl/*v)
SIM_TOP = sc_main
EXEC = $(VERILATOR_OUT)/$(VFILE)
VCFLAGS = -CFLAGS -I/lib/uvm-systemc/include
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
	rm -rf $(VERILATOR_OUT)

$(VERILATOR_OUT)/$(VMAKE): $(RTLFILES) 
	verilator $(CFLAGS) --sc $(RTLFILES) --Mdir $(VERILATOR_OUT) $(VCFLAGS)

$(EXEC): $(VERILATOR_OUT)/$(VMAKE) $(SIM_TOP).cpp $(CFILES)
	$(MAKE) -j -C $(VERILATOR_OUT) -f $(VMAKE) $(VFILE)__ALL.a
	$(MAKE) -j -C $(VERILATOR_OUT) -f $(VMAKE) $(SIM_TOP).o verilated.o
	cd $(VERILATOR_OUT) && g++ $(COMPILE_DEBUG) -L$(SYSTEMC_LIBDIR) -L$(UVM_LIBDIR) $(SIM_TOP).o $(VFILE)__ALL*.o verilated.o -o $(VFILE)  -lsystemc -luvm-systemc
