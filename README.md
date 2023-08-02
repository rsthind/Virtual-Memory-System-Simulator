# Virtual-Memory-System-Simulator

This simulator has five main files:
• page_splitting.h - Break down a virtual address into its components.
• paging.c - Initialize any necessary bookkeeping and implement address translation. • page_fault.c - Implement the page fault handler.
• page_replacement.c - Write frame eviction and the Clock Sweep algorithm.
• stats.c - Calculate the Average Access Time (AAT)

## Testing

For the commands below replace <trace > with the trace file you would like to run.

To run the random algorithm:

$ make
$./vm-sim -i traces/<trace >.trace -rrandom

To run the clocksweep algorithm:

$ make
$./vm-sim -i traces/<trace >.trace -rclocksweep