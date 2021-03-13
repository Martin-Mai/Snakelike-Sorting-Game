# Snakelike-Sorting-Game

## How the program run:
![](https://github.com/Martin-Mai/Snakelike-Sorting-Game/blob/main/SortingFlow.jpg)

## Technique:
Alternately sorting the rows and columns in Shearsort. The numbers to be sorted appear in a snakelike order after log2N+1 phases. 
Notice that even rows are always sorted in reverse order. The arrow direction indicates the sorting order (from small to large)

The threads would do the following in each phase of the algorithm.
1. By performing the appropriate number of wait operations on sempahores (or by a proper wait on a condition variable), block until the prior phase (if any) is finished.
2. Sort the row/column
3. Perform appropriate signal operations to signal the other threads to begin the next phase.

## POSIX pthreads
POSIX Threads, usually referred to as Pthreads, is an execution model that exists independently from a language, as well as a parallel execution model. It allows a program to
control multiple different flows of work that overlap in time. Each flow of work is referred
to as a thread, and creation and control over these flows is achieved by making calls to
the POSIX Threads API. You can find plenty of online resources to learns about the API.
Essentially you need to know how to (1) create threads, (2) terminate threads, and (3) use
mutex variables.

![](https://github.com/Martin-Mai/Snakelike-Sorting-Game/blob/main/Output.jpg)
