# UVM-SC-Tinker
Scratch work to try to convert the UVM-SV code from uvmprimer to UVM-SC. Also just general tinkering with SystemC.

## ENV variables set separately for reference:
    * export UVM_LIBDIR=/lib/uvm-systemc/lib-linux64/
    * export SYSTEMC_LIBDIR=/lib/systemc-2.3.1a/lib-linux64/
    * export LD_LIBRARY_PATH=$UVM_LIBDIR:$SYSTEMC_LIBDIR:$LD_LIBRARY_PATH
    * export SYSTEMC_INCLUDE=/lib/systemc-2.3.1a/include/
    * export VERILATOR_ROOT=/home/dph/verilator
    * export PATH=$VERILATOR_ROOT/bin:$PATH
    * export VERILATOR_INCLUDE=$VERILATOR_ROOT/include

## Hints/Notes
    * Compile UVM-SC and SystemC with symbols
    * GTKWave for waveform viewing