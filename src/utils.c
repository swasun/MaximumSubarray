/*******************************************************************************
 * Copyright (C) 2019 Charly Lamothe                                           *
 *                                                                             *
 * This file is part of MaximumSubarray.                                       *
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

#include "utils.h"

#include <string.h> /* strtok(), strlen() */
#include <stdlib.h> /* malloc(), free()   */
#include <fcntl.h>  /* open(), close()    */
#include <unistd.h> /* read()             */

int max(int a, int b) {
    return a > b ? a : b;
}

int count_sequence_elements(char *sequence) {
    int count;
    char *element;

    count = 0;

    element = strtok(sequence, " ");
    while (element != NULL) {
        count++;
        element = strtok (NULL, " ");
    }

    return count;
}

int *convert_sequence(char *sequence, int *n) {
    int *T, i;
    char *element;
    char *sequence2;

    /**
     * Create a new temporary sequence here, because strtok() used in count_sequence_elements()
     * isn't idempotent.
     */
    sequence2 = (char *)malloc((strlen(sequence) + 1) * sizeof(char));
    strcpy(sequence2, sequence);
    *n = count_sequence_elements(sequence2);
    free((void *)sequence2);

    T = (int *)malloc(*n * sizeof(int));
    memset(T, 0, *n * sizeof(int));
    i = 0;

    element = strtok(sequence, " ");
    while (element != NULL) {
        T[i] = atoi(element);
        element = strtok(NULL, " ");
        i++;
    }

    return T;
}

int generate_random_number(int fd) {
    int number = 0;
    read(fd, &number, sizeof(int));
    return number % AMPLITUDE;
}

int *generate_random_sequence(int fd, int n) {
    int *T, i;

    T = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        T[i] = generate_random_number(fd);
    }

    return T;
}

char *generate_random_str_sequence(int fd, int n) {
    int i, number;
    char *temp_sequence, *final_sequence, str_number[6];
    size_t initial_size, real_size;

    initial_size = strlen("-1000") * n;
    temp_sequence = (char *)malloc(((initial_size + 1) * n) * sizeof(char));
    real_size = 0;

    for (i = 0; i < n - 1; i++) {
        number = generate_random_number(fd);
        sprintf(str_number, "%d", number);
        sprintf(temp_sequence + real_size, "%s ", str_number);
        real_size += strlen(str_number) + strlen(" ");
    }

    final_sequence = (char *)malloc((strlen(temp_sequence) + 1) * sizeof(char));
    strcpy(final_sequence, temp_sequence);
    free((void *)temp_sequence);

    return final_sequence;
}

size_t get_file_size(FILE *file) {
    size_t file_size;

    file_size = -1;

    if (!file) {
        return -1;
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    return file_size;
}

int *read_sequence_file(const char *file_name, int *n) {
    char *content;
    size_t file_size;
    int *T, temp_n;
    FILE *file;

    temp_n = 0;
    content = NULL;
    file = fopen(file_name, "r");
    file_size = get_file_size(file);

    content = (char *)malloc((file_size + 1) * sizeof(char));
    memset(content, 0, (file_size + 1) * sizeof(char));

    if (fread(content, file_size, 1, file) == 0) {
        printf("[ERROR] Failed to read content file.\n");
        exit(EXIT_FAILURE);
    }

    fclose(file);

    T = convert_sequence(content, &temp_n);
    free((void *)content);
    *n = temp_n;

    return T;
}

void print_sequence(int *T, int n) {
    int i;

    printf("[");
    for (i = 0; i < n - 1; i++) {
        printf("%d, ", T[i]);
    }
    printf("%d]\n", T[i]);
}

void print_subsequence(int *T, int k, int l) {
    int i;

    printf("[");
    for (i = k; i < l; i++) {
        printf("%d, ", T[i]);
    }
    printf("%d]\n", T[i]);
}

void write_random_sequence(int fd, int n) {
    FILE *file;
    char *sequence;

    sequence = generate_random_str_sequence(fd, n);

    file = fopen("res/ss_random", "w+");

    fwrite(sequence, 1, strlen(sequence), file);

    fclose(file);

    free((void *)sequence);
}
