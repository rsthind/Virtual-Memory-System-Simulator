# Virtual-Memory-System-Simulator
</br>

This simulator has five main files: </br>
• page_splitting.h - Break down a virtual address into its components. </br>
• paging.c - Initialize any necessary bookkeeping and implement address translation. • page_fault.c - Implement the page fault handler. </br>
• page_replacement.c - Write frame eviction and the Clock Sweep algorithm. </br>
• stats.c - Calculate the Average Access Time (AAT) </br>
</br>

## Testing </br>
</br>
For the commands below replace (trace) with the trace file you would like to run.</br>
</br>
To run the random algorithm:</br>
</br>
$ make </br>
$./vm-sim -i traces/(trace).trace -rrandom </br>
</br>
To run the clocksweep algorithm: </br>
</br>
$ make </br>
$./vm-sim -i traces/(trace).trace -rclocksweep </br>