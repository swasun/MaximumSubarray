/*******************************************************************************
 * Copyright (C) 2019 Charly Lamothe                                           *
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
