# HDL

* combinational system
  * no memory
  * ex: BCD, ALU, mux, demux, boolean function

* Sequential System: constant clock signal
  * flipflops and latches for memory

> Terms

* ASIC: Rigid, implement only one code
* FPGA: Flexible
* HDLs (Hardware Description Languages): Computer languages that describe digital circuits, not programs to be executed
  * simulator may interpret the hardware, synthesis tool may implement the design in an FPGA or ASIC
  * Concurrent
  * [ex] verilog, VHDL

## Gate level

* (structural): Only contains wires and gates
* All connections are explicitly described
* The building blocks are single logic devices

![Gate Level](images/20210412_005710.png)

![Full Adder](images/20210412_005728.png)

## RTL (Register-transfer level)

* higher-level semantics than gates
* Most widely used level of abstractions

## Behavior level

* useful for simulation
* not always synthesizeable

## ModelSim

* Change Radix

![Radix](images/20210428_175501.png)

> Run

1. RTL Simulation
  ![RTL Simulation](images/20210423_180509.png)
1. Compile
  ![Compile](images/20210423_180531.png)
1. Select files
  ![Select files](images/20210423_180553.png)
1. Click main test file
  ![Click main test file](images/20210423_180612.png)
1. Add Wave
  ![Add Wave](images/20210423_180628.png)
1. Run all
  ![Run all](images/20210423_180703.png)

### Project

* mpf file

> Error

* unable to compile. ... file not found
  * project -> remove from project

> Create project

1. Select file
  ![Select file](images/20210430_220334.png)
1. Compile
1. Simulate Start Sim
  ![Simulate](images/20210430_220023.png)

## Quartus

> Howto : Create Project

![Set device](images/20210412_184542.png)

![Set Tool Settings](images/20210412_184709.png)

![Select Model sim path](images/20210412_185110.png)

> Error

* Error (12007): Top-level design entity "lab1" is undefined
  * project name must be same as `module_name` in .v file
