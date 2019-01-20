/*******************************************************************************
 * Copyright (C) 2019 Charly Lamothe, Doulkifouli Abdallah-Ali                 *
 *                                                                             *
 * This file is part of MaximumSubarrayProblem.                                *
 *                                                                             *
 *   Licensed under the Apache License, Version 2.0 (the "License");           *
 *   you may not use this file except in compliance with the License.          *
 *   You may obtain a copy of the License at                                   *
 *                                                                             *
 *   http://www.apache.org/licenses/LICENSE-2.0                                *
 *                                                                             *
 *   Unless required by applicable law or agreed to in writing, software       *
 *   distributed under the License is distributed on an "AS IS" BASIS,         *
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
 *   See the License for the specific language governing permissions and       *
 *   limitations under the License.                                            *
 *******************************************************************************/

#include "maximum_subarray.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>  /* open()          */
#include <unistd.h> /* read(), close() */
#include <getopt.h> /* getopt_long()   */
#include <time.h>   /* clock()            */
#include <assert.h> /* assert()        */

/**
 * Print the usage.
 */
static void print_usage(char **argv) {
    printf("\n");
    printf("Usage: %s <algorithm> <input> <options>\n", argv[0]);
    printf("\n");
    printf("Algorithms: --naive | --naive_opti | --divide_conquer | --kadane\n");
    printf("--naive: compute the maximum subarray using a naive approch. O(n³)\n");
    printf("--naive_opti: compute the maximum subarray using a naive approch and applying a simple optimization S(k,l) = S(k,l-1) + T[l].\n");
    printf("--divide_conquer: compute the maximum subarray by dividing recursively the problem by applying the divide-and-conquer paradigm.\n");
    printf("--kadane: compute the maximum subarray in linear time using the Kadane's algorithm.\n");
    printf("\n");
    printf("Inputs: ((-i | --stdin) <n0..ni>) | ((-r | --random) <size>) | ((-f | --file) <file_name>)\n");
	printf("-i ou --stdin: the sequence is write in the command line, surrounded by \" where each element is separated with a space.\n");
    printf("-r ou --random: the sequence is randomly generated, with a specified size.\n");
    printf("-f ou --file: the sequence is provide by a file, where each element where each element is separated with a space.\n");
    printf("\n");
    printf("-h ou --help: print the current usage.\n");
    printf("-a ou --print: print the input sequence and the ouput subsequence.\n");
    printf("-g ou --gen_random: generate a random sequence of size n in a file called 'random'.\n");
    printf("-t ou --test: execute a serie of test by comparing algorithms outputs with known results.\n");
    printf("\n");
}

/**
 * List of available options in program input.
 */
static struct option options[] = {
    { "naive", no_argument, NULL, '0' },
    { "naive_opti", no_argument, NULL, '1' },
    { "divide_conquer", no_argument, NULL, '2' },
    { "kadane", no_argument, NULL, '3' },
    { "stdin", required_argument, NULL, 'i' },
    { "random", required_argument, NULL, 'r' },
    { "gen_random", required_argument, NULL, 'g' },
    { "file", required_argument, NULL, 'f' },
    { "help", no_argument, NULL, 'h' },
    { "print", no_argument, NULL, 'a' },
    { "test", no_argument, NULL, 't' },
    { NULL, 0, NULL, 0 }
};

/**
 * Perform a bettery of tests where the results are known in advance,
 * for small inputs.
 */
void perform_tests() {
    int *T_n_10_1, *T_n_10_2;
    int *T_n_11_1, *T_n_11_2;
    int *T_n_100_1, *T_n_100_2;
    int *T_n_101_1, *T_n_101_2;
    int n;
    int k, l, sum;

    /* Charge tous les fichiers de tests contenant les séquences */
    T_n_10_1 = read_sequence_file("res/test_n_10_1", &n);
    T_n_10_2 = read_sequence_file("res/test_n_10_2", &n);
    T_n_11_1 = read_sequence_file("res/test_n_11_1", &n);
    T_n_11_2 = read_sequence_file("res/test_n_11_2", &n);
    T_n_100_1 = read_sequence_file("res/test_n_100_1", &n);
    T_n_100_2 = read_sequence_file("res/test_n_100_2", &n);
    T_n_101_1 = read_sequence_file("res/test_n_101_1", &n);
    T_n_101_2 = read_sequence_file("res/test_n_101_2", &n);

    printf("Test of all algorithms\n\n");

    /* Test of algorithm 1 */
    printf("Tests of the naive algorithm (1)\n");
    maximum_subarray_naive(T_n_10_1, 10, &k, &l);
    assert(k == 8 && l == 8);
    maximum_subarray_naive(T_n_10_2, 10, &k, &l);
    assert(k == 2 && l == 9);
    maximum_subarray_naive(T_n_11_1, 11, &k, &l);
    assert(k == 2 && l == 4);
    maximum_subarray_naive(T_n_11_2, 11, &k, &l);
    assert(k == 0 && l == 3);
    maximum_subarray_naive(T_n_100_1, 100, &k, &l);
    assert(k == 17 && l == 74);
    maximum_subarray_naive(T_n_100_2, 100, &k, &l);
    assert(k == 2 && l == 46);
    maximum_subarray_naive(T_n_101_1, 101, &k, &l);
    assert(k == 37 && l == 84);
    maximum_subarray_naive(T_n_101_2, 101, &k, &l);
    assert(k == 7 && l == 94);
    printf("The algorithm maximum_subarray_naive (1) succeed all tests.\n\n");

    /* Test of algorithm 2 */
    printf("Test of the optimized naive algorithm (2)\n");
    maximum_subarray_naive_optimized(T_n_10_1, 10, &k, &l);
    assert(k == 8 && l == 8);
    maximum_subarray_naive_optimized(T_n_10_2, 10, &k, &l);
    assert(k == 2 && l == 9);
    maximum_subarray_naive_optimized(T_n_11_1, 11, &k, &l);
    assert(k == 2 && l == 4);
    maximum_subarray_naive_optimized(T_n_11_2, 11, &k, &l);
    assert(k == 0 && l == 3);
    maximum_subarray_naive_optimized(T_n_100_1, 100, &k, &l);
    assert(k == 17 && l == 74);
    maximum_subarray_naive_optimized(T_n_100_2, 100, &k, &l);
    assert(k == 2 && l == 46);
    maximum_subarray_naive_optimized(T_n_101_1, 101, &k, &l);
    assert(k == 37 && l == 84);
    maximum_subarray_naive_optimized(T_n_101_2, 101, &k, &l);
    assert(k == 7 && l == 94);
    printf("The algorithm maximum_subarray_naive (2) succeed all tests.\n\n");

    /* Test of algorithm 3 */
    printf("Test of the divide and conquer algorithm (3)\n");
    maximum_subarray_divide_conquer(T_n_10_1, 0, 10-1, &sum, &k, &l);
    assert(k == 8 && l == 8);
    maximum_subarray_divide_conquer(T_n_10_2, 0, 10-1, &sum, &k, &l);
    assert(k == 2 && l == 9);
    maximum_subarray_divide_conquer(T_n_11_1, 0, 11-1, &sum, &k, &l);
    assert(k == 2 && l == 4);
    maximum_subarray_divide_conquer(T_n_11_2, 0, 11-1, &sum, &k, &l);
    assert(k == 0 && l == 3);
    maximum_subarray_divide_conquer(T_n_100_1, 0, 100-1, &sum, &k, &l);
    assert(k == 17 && l == 74);
    maximum_subarray_divide_conquer(T_n_100_2, 0, 100-1, &sum, &k, &l);
    assert(k == 2 && l == 46);
    maximum_subarray_divide_conquer(T_n_101_1, 0, 101-1, &sum, &k, &l);
    assert(k == 37 && l == 84);
    maximum_subarray_divide_conquer(T_n_101_2, 0, 101-1, &sum, &k, &l);
    assert(k == 7 && l == 94);
    printf("The algorithm maximum_subarray_divide_conquer (3) succeed all tests.\n\n");

    /* Test of algorithm 4 */
    printf("Test of Kadane's algorithm (4)\n");
    maximum_subarray_kadane(T_n_10_1, 10, &k, &l);
    assert(k == 8 && l == 8);
    maximum_subarray_kadane(T_n_10_2, 10, &k, &l);
    assert(k == 2 && l == 9);
    maximum_subarray_kadane(T_n_11_1, 11, &k, &l);
    assert(k == 2 && l == 4);
    maximum_subarray_kadane(T_n_11_2, 11, &k, &l);
    assert(k == 0 && l == 3);
    maximum_subarray_kadane(T_n_100_1, 100, &k, &l);
    assert(k == 17 && l == 74);
    maximum_subarray_kadane(T_n_100_2, 100, &k, &l);
    assert(k == 2 && l == 46);
    maximum_subarray_kadane(T_n_101_1, 101, &k, &l);
    assert(k == 37 && l == 84);
    maximum_subarray_kadane(T_n_101_2, 101, &k, &l);
    assert(k == 7 && l == 94);
    printf("The algorithm maximum_subarray_kadane (4) succeed all tests.\n\n");

    /* Deallocate arrays */
    free((void *)T_n_10_1);
    free((void *)T_n_10_2);
    free((void *)T_n_11_1);
    free((void *)T_n_11_2);
    free((void *)T_n_100_1);
    free((void *)T_n_100_2);
    free((void *)T_n_101_1);
    free((void *)T_n_101_2);
}

int main(int argc, char **argv) {
    int *T, n;
    int k, l;
    int opt, naive, naive_opti, divide_conquer, kadane, random_sequence_size, print, gen_random, test;
    char *sequence, *file_name;
    int fd, clock_begin, clock_end, sum;

    sequence = NULL;
    T = NULL;
    naive = 0;
    naive_opti = 0;
    divide_conquer = 0;
    kadane = 0;
    random_sequence_size = 0;
    sequence = NULL;
    file_name = NULL;
    fd = 0;
    print = 0;
    sum = 0;
    gen_random = 0;
    test = 0;

    /* Parse the differents specified options of program input */
    while ((opt = getopt_long(argc, argv, "f:r:h:i:d:t", options, NULL)) != -1) {
        switch (opt) {
            /* Specify which algorith use */

            /* Algorithm 1 */
            case '0':
               naive = 1;
            break;

            /* Algorithm 2 */
            case '1':
                naive_opti = 1;
            break;

            /* Algorithm 3 */
            case '2':
                divide_conquer = 1;
            break;

            /* Algorithm 4 */
            case '3':
                kadane = 1;
            break;

            /* Specify which type of input for the sequence */

            /* Input the sequence in stdin */
            case 'i':
                sequence = optarg;
            break;

            /* Generate the sequence randomly */
            case 'r':
                random_sequence_size = atoi(optarg);
                if (random_sequence_size == 0) {
                    fprintf(stderr, "[ERROR] the specified size of the random sequence is invalid.\n");
                    exit(EXIT_FAILURE);
                }
            break;

            /* Load the input sequence from an existing text file */
            case 'f':
                file_name = optarg;
            break;

            /* Specify additional options */

            case 'h':
                print_usage(argv);
                exit(EXIT_SUCCESS);
            break;

            /* Specify if the input sequence have to be print (for small inputs) */
            case 'd':
                print = 1;
            break;

            /* To geneerate a random sequence and write it in a file */
            case 'g':
                gen_random = atoi(optarg);
            break;

            /* Perform the battery of tests */
            case 't':
                test = 1;
            break;

            /* If an user input is invalid */
            default:
                print_usage(argv);
                exit(EXIT_FAILURE);
        }
    }

    /* If the random generation option is specified in program input */
    if (gen_random) {
        fd = open("/dev/urandom", O_RDONLY);
        write_random_sequence(fd, gen_random);
        close(fd);
        exit(EXIT_SUCCESS);
    }

    /* If the test option is specified in program input */
    if (test) {
        perform_tests();
        exit(EXIT_SUCCESS);
    }

    /* If none of the available algorithms is spacified, the program stops */
    if (!naive && !naive_opti && !divide_conquer && !kadane) {
        printf("[ERROR] None of the available algorithms is spacified.\n");
        print_usage(argv);
        exit(EXIT_FAILURE);
    }

    /* If the sequence is specified in stdin */
    if (sequence) {
        T = convert_sequence(sequence, &n);
    }
    /* Else if the sequence is generated randomly */
    else if (random_sequence_size != 0) {
        clock_begin = clock();
        fd = open("/dev/urandom", O_RDONLY);
        T = generate_random_sequence(fd, random_sequence_size);
        n = random_sequence_size;
        close(fd);
        clock_end = clock();
        printf("Generation of the sequence in %.3fs.\n", (double)(clock_end - clock_begin) / CLOCKS_PER_SEC);
    }
    /* Else if the sequence is existing in a text file */
    else if (file_name) {
        T = read_sequence_file(file_name, &n);
    }
    /* Else if no sequence is specified in input, the program stops */
    else {
        printf("[ERROR] No sequence is specified in input.\n");
        print_usage(argv);
        exit(EXIT_FAILURE);
    }

    /* If the -d option is specified, the input sequence is print */
    if (print) {
        printf("Séquence d'entrée: ");
        print_sequence(T, n);
        printf("\n");
    }

    /* We record the current time */
    clock_begin = clock();

    /* If the naive algorithm (1) is specified */
    if (naive) {
        sum = maximum_subarray_naive(T, n, &k, &l);
    }
    /* If the optimized naive algorithm (2) is specified */
    else if (naive_opti) {
        sum = maximum_subarray_naive_optimized(T, n, &k, &l);
    }
    /* If the divide-and-conquer algorithm (3) is specified */
    else if (divide_conquer) {
        maximum_subarray_divide_conquer(T, 0, n-1, &sum, &k, &l);
    }
    /* If the Kadane's algorithm (4) is specified */
    else if (kadane) {
        sum = maximum_subarray_kadane(T, n, &k, &l);
    }

    /**
     * We record the current time, then we substract it with the previous recorded time
     * in order the compute the execution time of the runned algorithm.
     */
    clock_end = clock();
    printf("Execution of the algorithm in %fs.\n", (double)(clock_end - clock_begin) / CLOCKS_PER_SEC);

    /* Print the sum, the indexes k and l and the subsequence */
    if (print) {
        printf("T[%d..%d] of sum %d is ", k, l, sum);
        print_subsequence(T, k, l);
    } else {
        printf("T[%d..%d] of sum %d", k, l, sum);
    }
    printf("\n");

    /* Deallocate the array */
    if (T) {
        free((void *)T);
    }
    
    return EXIT_SUCCESS;
}
