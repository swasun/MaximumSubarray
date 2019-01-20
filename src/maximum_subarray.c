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

#include "maximum_subarray.h"
#include "utils.h"

#include <stdlib.h>

int maximum_subarray_naive(int *T, int n, int *k, int *l) {
    int i, j, sum, max_sum, **subsequences, temp_k, temp_l, m, final_k, final_l;

    max_sum = T[0];
    sum = 0;
    temp_k = 0;
    temp_l = 0;
    final_k = 0;
    final_l = 0;
    m = n;

    if (n == 1) {
        *k = 0;
        *l = 0;
        return T[0];
    }

    /**
     * Create a array of subsequences, of Ifze n, in two dimenIfons
     * that contains all the possible subsequences in the array T.
     */

    /* Allocate the main array */
    subsequences = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++) {
        /* Allocate the current subsequence */
        subsequences[i] = (int *)malloc(m * sizeof(int));
        m--;
        for (j = i; j < n; j++) {
            for (m = i; m <= j; m++) {
                subsequences[i][m] = T[m];
            }
        }
    }

    /**
     * Iterate the subsequences in the 
     * two dimenIfonal array
     */


    /* For each array of subsequences */
    for (i = 0; i < n; i++) {
        /* Update temporary k index */
        temp_k = i;
        /* For each subsequence of the array */
        for (j = i; j < n; j++) {
            /* Update temporary l index */
            temp_l = j;
            /* Compute the temporary sum of the current subsequence */
            for (m = i; m <= j; m++) {
                sum += subsequences[i][m];
            }

            /**
             * Compare the current subsequence with the largest known
             * subsequence
             */
            if (sum > max_sum) {
                /**
                 * If the current subsequence is larger than the other,
                 * we update the largest subsequence, and the finals indexes
                 * k and l.
                 */
                max_sum = sum;
                final_k = temp_k;
                final_l = temp_l;
            }

            sum = 0;
        }
    }

    /* Returns the couple of indexes k and l */
    *k = final_k;
    *l = final_l;

    /* Deallocate the subsequences of subsequences */
    for (i = 0; i < n; i++) {
        free((void *)subsequences[i]);
    }
    free((void *)subsequences);

    return max_sum;
}

int maximum_subarray_naive_optimized(int *T, int n, int *k, int *l) {
    int max_sum, sum, i, j, temp_k, temp_l;

    max_sum = T[0];
    sum = 0;
    temp_k = 0;
    temp_l = 0;

    if (n == 1) {
        *k = 0;
        *l = 0;
        return T[0];
    }

    /* For each subsequence */
    for (i = 0; i < n; i++) {
        /* sum of the subsequence T[i..j] */
        
        /* Reinitialization of the sum */
        sum = 0;
        
        /* For each element of the current subsequence */
        for (j = i; j < n; j++) {
            sum += T[j];
            
            /**
             * If the sum of the current subsequence is larger
             * that the previous computed, we update the
             * maximal sum.
             */
            if (sum > max_sum) {
                max_sum = sum;
                temp_k = i;
                temp_l = j;
            }
        }
    }

    /* We update k and l indexes following the previous computed durint the comparaison */
    *k = temp_k;
    *l = temp_l;

    return max_sum;
}

static void maximum_subarray_middle(int *T, int k, int l, int *sum, int *final_k, int *final_l) {
    int i, temp_sum, left_sum, right_sum, middle;

    temp_sum = 0;

    /**
     * Initialize the default sum with the minimal value, in case that
     * we begin the array with an element close to the min value of
     * an integer.
     */
    left_sum = MIN_INT;
    right_sum = MIN_INT;

    /* Compute the middle index of the array from the sizes of left and right array */
    middle = (k + l) / 2;

    *final_k = 0;
    *final_l = 0;

    /**
     * Compute the largest sum of the left part of the array
     * by iterating the left part of the array.
     */
    for (i = middle; i >= k; i--) {
        temp_sum += T[i];
        if (temp_sum > left_sum) {
            left_sum = temp_sum;
            *final_k = i;
        }
    }

    /* Reinitialize the sum */
    temp_sum = 0;

    /**
     * Compute the largest sum of the right part of the array
     * by iterating the right part of the array.
     */
    for (i = middle+1; i <= l; i++) {
        temp_sum += T[i];
        if (temp_sum > right_sum) {
            right_sum = temp_sum;
            *final_l = i;
        }
    }

    /* Compute the middle sum by adding the two maximal sums of each part of the array */
    *sum = left_sum + right_sum;
}

void maximum_subarray_divide_conquer(int *T, int k, int l, int *sum, int *final_k, int *final_l) {
    int middle, max_sum;
    int temp_left_k, temp_left_l, left_sum;
    int temp_right_k, temp_right_l, right_sum;
    int temp_middle_k, temp_middle_l, middle_sum;

    /**
     * Stopping condition
     * If k and l indexes are equals, then we already have our indexes and sum
     */
    if (k == l) {
        *sum = T[k];
        *final_k = k;
        *final_l = l;
        return;
    }
    
    /* Compute the middle index of the array from the sizes of the left and right part of the array */
    middle = (k+l)/2;

    /* Compute the sums of the left and right parts of the array */
    maximum_subarray_divide_conquer(T, k, middle, &left_sum, &temp_left_k, &temp_left_l);
    maximum_subarray_divide_conquer(T, middle+1, l, &right_sum, &temp_right_k, &temp_right_l);

    /* Compute the sum of the middle part of the array */
    maximum_subarray_middle(T, k, l, &middle_sum, &temp_middle_k, &temp_middle_l);
    
    /* Compute if the maximal sum between the three results */
    max_sum = max(left_sum, max(right_sum, middle_sum));
    
    /* The indexes k and l are those with the maximum sum */
    if (max_sum == left_sum) {
        *sum = left_sum;
        *final_k = temp_left_k;
        *final_l = temp_left_l;
    }
    else if (max_sum == right_sum) {
        *sum = right_sum;
        *final_k = temp_right_k;
        *final_l = temp_right_l;
    }
    else if (max_sum == middle_sum) {
        *sum = middle_sum;
        *final_k = temp_middle_k;
        *final_l = temp_middle_l;
    }
}

int maximum_subarray_kadane(int *T, int n, int *k, int *l) {
    int sum, max_sum, temp_k, temp_l, i, next_index;

    sum = 0;
    /* At the beginning the best known sum is the first element of the array */
    max_sum = T[0];
    temp_k = 0;
    temp_l = 0;
    next_index = 0;

    /**
     * Stopping condition
     * If les indexes k and l are equals, then we already have our indexes and sum
     */
    if (n == 1) {
        *k = 0;
        *l = 0;
        return T[0];
    }
 
     /* For each element of T */
    for (i = 0; i < n; i++) {
        /* We increase our continuous sum */
        sum += T[i];
     
         /* If our continuous sum exceeds the last maximum known sum */
        if (sum > max_sum) {
            /* We update the sum and the indexes */
            max_sum = sum;
            temp_k = next_index;
            temp_l = i;
        }
     
        /* If our continuous sum is < 0, we reinitialize our sum */
        if (sum < 0) {
            sum = 0;
            next_index = i + 1;
        }

        /**
         * Else if our sum isn't larger than the last known maximum sum
         * and that our sum isn't negative, we do nothing.
         * Then, if we incremente our sum we a nagative element, we wait and see
         * the following elements which might be more interesting.
         */
    }

    /* Returns the final indexes and the last maximum known sum */

    *k = temp_k;
    *l = temp_l;

    return max_sum;
}
