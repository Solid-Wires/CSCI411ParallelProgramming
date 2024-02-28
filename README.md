# CSCI 411 Project Lab Parallel Programming

Jared Whytsell

This assignment is simply changing the provided trapezoid definite integral calculator into a parallel program with different amounts of threads.

# How to run

Simply run make to create the executable. You should see bin and obj directories created in the workspace. Should you want the lecture examples that we discussed, run make lect_programs to see those.

bin/trap runs the program.
All of the lecture programs are located and ran at bin/lectures/.

The program walks you through the inputs that it needs.

# Analysis

With input of endpoints 2 to 10 of 1,000,000 trapezoids, these are the timings of the output of 330.667:

| Timing (s)   |   Num of threads |
|--------------|------------------|
| 0.024424     |        4         |
| 0.0160349    |        8         |
| 0.0144189    |       16         |
| 0.0120077    |       32         |

It looks like it was already pretty fast with just 4 threads, but adding more seemed to increase
the speed of computations by a certain scale.
