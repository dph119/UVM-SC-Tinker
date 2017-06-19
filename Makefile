VFILE = Vtinyalu
VMAKE = $(VFILE).mk
CFLAGS = -Wno-WIDTH
VERILATOR_OUT = out
VERILATOR_OUT_FILES = $(wildcard $(VERILATOR_OUT)/*)
RTLFILES = $(wildcard rtl/*v)
SIM_TOP = sc_main
EXEC = $(VERILATOR_OUT)/$(VFILE)

build: $(EXEC)

run: $(EXEC)
	./$(EXEC)

$(VERILATOR_OUT)/$(VMAKE): $(RTLFILES) 
	verilator $(CFLAGS) --sc $(RTLFILES) --Mdir $(VERILATOR_OUT)

$(EXEC): $(VERILATOR_OUT)/$(VMAKE) $(SIM_TOP).cpp
	$(MAKE) -j -C $(VERILATOR_OUT) -f $(VMAKE) $(VFILE)__ALL.a
	$(MAKE) -j -C $(VERILATOR_OUT) -f $(VMAKE) $(SIM_TOP).o verilated.o
	cd $(VERILATOR_OUT) && g++ -L$(SYSTEMC_LIBDIR) $(SIM_TOP).o $(VFILE)__ALL*.o verilated.o -o $(VFILE) -lsystemc
