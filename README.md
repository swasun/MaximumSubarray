A simple program that implements four algorithms to compute the Maximum Subarray Problem (old school project, Complexity class, 2017).

## Complexity

*Naive algorithm* in <a href="https://www.codecogs.com/eqnedit.php?latex=O(n^3)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(n^3)" title="O(n^3)" /></a> \
*Optimized version of naive algorithm* in <a href="https://www.codecogs.com/eqnedit.php?latex=O(n^2)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(n^2)" title="O(n^2)⁾" /></a> \
*Divide-and-conquer algorithm* in <a href="https://www.codecogs.com/eqnedit.php?latex=O(n&space;\&space;log&space;\&space;n)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(n&space;\&space;log&space;\&space;n)" title="O(n \ log \ n)" /></a> \
*Kadane's algorithm* in <img src="https://latex.codecogs.com/gif.latex?O(n)"/>

## Usage

```
mkdir obj && mkdir bin && make
./bin/maximum_subarray --help

Usage: ./bin/maximum_subarray <algorithm> <input> <options>

Algorithms: --naive | --naive_opti | --divide_conquer | --kadane
--naive: compute the maximum subarray using a naive approch. O(n³)
--naive_opti: compute the maximum subarray using a naive approch and applying a simple optimization S(k,l) = S(k,l-1) + T[l].
--divide_conquer: compute the maximum subarray by dividing recursively the problem by applying the divide-and-conquer paradigm.
--kadane: compute the maximum subarray in linear time using the Kadane's algorithm.

Inputs: ((-i | --stdin) <n0..ni>) | ((-r | --random) <size>) | ((-f | --file) <file_name>)
-i ou --stdin: the sequence is write in the command line, surrounded by " where each element is separated with a space.
-r ou --random: the sequence is randomly generated, with a specified size.
-f ou --file: the sequence is provide by a file, where each element where each element is separated with a space.

-h ou --help: print the current usage.
-a ou --print: print the input sequence and the ouput subsequence.
-g ou --gen_random: generate a random sequence of size n in a file called 'random'.
-t ou --test: execute a serie of test by comparing algorithms outputs with known results
```

## Using the code

```c
#include "maximum_subarray.h"

int *T, n, k, l, sum;

/* Fill T and n */
/* [...] */

sum = maximum_subarray_kadane(T, n, &k, &l);
```

## Experiments

On the naive algorithm with an input of size 1K:
```
./bin/maximum_subarray --naive --random 1000
Generation of the sequence in 0.001s.
Execution of the algorithm in 0.886747s.
```

On the optimized naive algorithm with an input of size 1K:
```
./bin/maximum_subarray --naive_opti --random 1000
Generation of the sequence in 0.001s.
Execution of the algorithm in 0.001820s.
```

On the divide and conquer algorithm with an input of size 1K:
```
./bin/maximum_subarray --divide_conquer --random 1000
Generation of the sequence in 0.001s.
Execution of the algorithm in 0.000187s.
```

On the Kadane's algorithm with an input of size 1K:
```
./bin/maximum_subarray --kadane --random 1000
Generation of the sequence in 0.001s.
Execution of the algorithm in 0.000009s.
```

On the Kadane's algorithm with an input of size 10K:
```
./bin/maximum_subarray --kadane --random 10000
Generation of the sequence in 0.007s.
Execution of the algorithm in 0.000037s.
```

On the Kadane's algorithm with an input of size 100K:
```
./bin/maximum_subarray --kadane --random 100000
Generation of the sequence in 0.056s.
Execution of the algorithm in 0.000310s.
```

On the Kadane's algorithm with an input of size 1M:
```
./bin/maximum_subarray --kadane --random 1000000
Generation of the sequence in 0.495s.
Execution of the algorithm in 0.003076s.
```

## Authors

* Charly Lamothe
* Doulkifouli Abdallah-Ali
