/*************************************************************************************
 * MIT License                                                                       *
 *                                                                                   *
 * Copyright (C) 2017 Charly Lamothe, Doulkifouli Abdallah-Ali                       *
 *                                                                                   *
 * This file is part of MaximumSubarrayProblem.                                      *
 *                                                                                   *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy    *
 *   of this software and associated documentation files (the "Software"), to deal   *
 *   in the Software without restriction, including without limitation the rights    *
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell       *
 *   copies of the Software, and to permit persons to whom the Software is           *
 *   furnished to do so, subject to the following conditions:                        *
 *                                                                                   *
 *   The above copyright notice and this permission notice shall be included in all  *
 *   copies or substantial portions of the Software.                                 *
 *                                                                                   *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      *
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        *
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     *
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          *
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   *
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   *
 *   SOFTWARE.                                                                       *
 *************************************************************************************/

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>  /* FILE   */
#include <stddef.h> /* size_t */

/* Min value of an integer in C */
#define MIN_INT -2147483648

/* Delimiting bound of random numbers: [-1000..+1000] */
#define AMPLITUDE 1000

int max(int a, int b);

/**
 * Count the number of elements in a sequence where the elements are separated by spaces.
 */
int count_sequence_elements(char *sequence);

/**
 * Convert a sequence of elements separated by spaces in an integer arrays of size n.
 */
int *convert_sequence(char *sequence, int *n);

/**
 * Generate a random number reading /dev/urandom, bound by an amplitude (1000 by default).
 */
int generate_random_number(int fd);

/**
 * Generate an array of n random numbers.
 */
int *generate_random_sequence(int fd, int n);

/**
 * Generate a random number sequence of size n using the specified
 * file descriptor. Numbers are separated by spaces.
 */
char *generate_random_str_sequence(int fd, int n);

size_t get_file_size(FILE *file);

/**
 * Create an integers array from a file.
 * Numbers if the file must be integers,
 * separated by spaces.
 * 
 * @param file_name The path and the name of the input file
 * @return T The integer array
 * @return n The size of array T
 */
int *read_sequence_file(const char *file_name, int *n);

/**
 * Print to stdout a sequence where each group of 10 elements
 * is separated with a new line.
 */
void print_sequence(int *T, int n);

/**
 * Print the subsequence T[k..l]
 */
void print_subsequence(int *T, int k, int l);

void write_random_sequence(int fd, int n);

#endif
