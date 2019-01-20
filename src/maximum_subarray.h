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

#ifndef MAXIMUM_SUBARRAY_H
#define MAXIMUM_SUBARRAY_H

/**
 * Find the array with the largest subarray of array T
 * of size n.
 *
 * @param T Array of integers
 * @param n Size of T array
 * @return k Left index of largest subarray
 * @return l Right index of largest subarray
 * @return sum Sum of the largest subarray
 *
 * Algorithm
 * Compute all possible subsequences.
 * Compute the sum of all subsequences, and keep
 * the indices of the largest sum.
 * Return the indices by parameter.
 *
 * Complexity: O(n³)
 */
int maximum_subarray_naive(int *T, int n, int *k, int *l);

/* 
 * Find the array with the largest subarray of array T
 * of size n.
 *
 * @param T Array of integers
 * @param n Size of T array
 * @return k Left index of largest subarray
 * @return l Right index of largest subarray
 * @return sum Sum of the largest subarray
 *
 * Algorithm
 * Compute the subsequences on the fly, and apply the optimization
 * S(k, l) = S(k, l - 1) + T[l] avec the line sum += T[j].
 *
 * Complexity: O(n²)
 */
int maximum_subarray_naive_optimized(int *T, int n, int *k, int *l);

/* 
 * Find the array with the largest subarray of array T
 * of size n.
 *
 * Algorithm
 * Compute the best left sum
 * Compute the best right sum
 * Compute the best middle sum
 * Compute the maximum between the three computed sums

 * @param T Array of integers
 * @param k L'indice courant du début de T
 * @param l L'indice courant de la fin de T
 * @return sum Sum of the largest subarray
 * @return final_k Left index of largest subarray
 * @return final_l Right index of largest subarray
 *
 * Complexity
 * - If k == l : O(1)
 * - Divide the problem in two : T(N/2)
 * - Compute the middle subsequence : O(N)
 * - Resolve the maximum between each sum : O(1)
 * Thus T(1) = O(1) and
 * For N > 1, T(N) = 2T(N/2) + O(N)
 * T(N) = O(NlogN)
 */
void maximum_subarray_divide_conquer(int *T, int k, int l, int *sum, int *final_k, int *final_l);

/**
 * Find the array with the largest subarray of array T
 * of size n.
 *
 * Algorithm
 * Find the largest continuous sum using the sum variable,
 * which is compared to the largest known sum at each iteration
 * (by default the first element).
 * If the sum is negative, the sum is reinitialized and we
 * advance to index k.
 * The final sum is the largest found sum.
 *
 * @param T Array of integers
 * @param n Size of T array
 * @return k Left index of largest subarray
 * @return l Right index of largest subarray
 * @return sum Sum of the largest subarray
 *
 * Complexity: O(n) because there's only a single iteration of T
 */
int maximum_subarray_kadane(int *T, int n, int *k, int *l);

#endif
