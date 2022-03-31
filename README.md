# Threads-Posix
A C simple exercise implementing POSIXs Threads to calculate Pi using the Leibniz formula for Pi.
The Threads implementation were tested with 3 different proccesors into Windows and Ubuntu SO
*  AMD A12-9720P 4 cores 4 threads 3.6Ghz, 16 GB DDR4 RAM 933 Mhz.
*  Intel Xeon W3520 4 cores 4 threads 2.2Ghz, 4 GB DDR3 RAM 1333 Mhz.
*  Google Collab Basic Notebook Intel Xeon (no specific reference found) 1 core 2 threads 2.2 Ghz, 12,69 RAM.  

I prove with maximum value of 4 threads. The purpose of that is to prove the execution time giving one thread per core processor, if you have a PC with more or less cores, feel free to change the threads value in C code.

The development was finished. 
But still a problem with AMD processor, cause the execution time increases adding threads, probably each thread is assigned in one core instead of 1 thread per core. 
This problem for now no solution yet, IDK if this bug only are in this AMD processor or it's a general problem.
