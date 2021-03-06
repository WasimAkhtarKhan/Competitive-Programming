/*
 * Problem Statement: https://www.spoj.com/problems/BYTESM2/
 * Author: striker
 *
 * Copyright 2020 striker
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
*/

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <iomanip>
#include <map>
#include <numeric>
#include <queue>
#include <stack>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/*START OF CODE-TEMPLATE*/

typedef unsigned long long ull_t;
typedef long long ll_t;

#define FAST_IO(value) std :: ios :: sync_with_stdio(value); std :: cin.tie(NULL); std :: cout.tie(NULL)

#define MOD 1000000007 // Constant (prime number) used in most competitive programming problems to reduce the answer to a 32-bit integer.
#define PI 3.141592653589793 // Number of digits(15) of Pi which JPL uses for Interplanetary Caculations.
#define GOLDEN_RATIO 1.618033988749895 // Number of digits(15).
#define INF_32_BIT_US_INT 0xFFFFFFFF // Maximum value which can be stored in an unsigned int (32-Bit).
#define INF_64_BIT_US_INT 0xFFFFFFFFFFFFFFFF // Maximum value which can be stored in an unsigned long long (64-Bit).
#define NEW_LINE '\n' // Created because sometimes std :: endl makes the code slower due to clearance of buffer after printing new-line.

#define COMPUTE_GCD(a, b) std :: __gcd((a), (b))
#define COMPUTE_LCM(a, b) (a * ((b) / COMPUTE_GCD(a, b)))

// C and C++ "%" operator is not a modular arithmetic operator rather it's a remainder operator which gives remainder when a / b.
// Implementation is based on the fact that a % b = a - (b * (a / b)), where a = dividend, b = divisor, a / b = quotient.
// Refer: https://stackoverflow.com/questions/11720656/modulo-operation-with-negative-numbers
// Time Complexity: O(1).
ll_t compute_mod(ll_t a, ll_t b) {
    assert(b > 0); // Denominator must be positive.
    ll_t rem = a % b;
    return rem < 0 ? b + rem : rem;
}

// The function computes the total number of divisors for the given n. i.e. d(n).
// Time-Complexity: O(sqrt(n)).
ll_t compute_total_divisors(ll_t n) {
    ll_t total_divisors = 0;
    for(ll_t i = 1; i <= (n / i); ++i) {
        if(!(n % i)) {
            if((n / i) == i) {
                ++total_divisors;
                continue;
            }
            total_divisors += 2;
        }
    }
    return total_divisors;
}

// The code computes whether the given number (n) is a perfect square or not based on the fact that, a number is a perfect square if it has odd number of divisors.
// Refer: https://math.stackexchange.com/questions/906159/a-number-is-a-perfect-square-if-and-only-if-it-has-odd-number-of-positive-diviso
// Time-Complexity: O(sqrt(n)).
bool check_perfect_sequare(ll_t n) {
    return compute_total_divisors(n) % 2 ? true : false;
}

// Computes the number of set-bits in the binary representation of n (64-Bit).
#define COMPUTE_SET_BITS(number) __builtin_popcountll(number)

// Computes the parity of the number n (64-Bit) i.e. parity is 0 if the number of set-bits is even otherwise odd.
#define COMPUTE_PARITY(number) __builtin_parity(number)

// Computes the number of leading zeroes in the binary representation of n (64-Bit). The value will be 64 - (number of bits required to represent n).
#define COMPUTE_LEADING_ZEROES(number) __builtin_clzll(number)

// Computes the number of trailing zeroes in the binary representation of n (64-Bit). The value will always be zeroe if n is odd.
#define COMPUTE_TRAILING_ZEROES(number) __builtin_ctzll(number)

/*END-OF CODE-TEMPLATE*/

static int compute_maximum_path_cost(const std :: vector<std :: vector <int>> &, const int, const int);

int main(void) {
    FAST_IO(0);
    int test;
    std :: cin >> test;
    while(test--) {
        int h, w;
        std :: cin >> h >> w;
        std :: vector <std :: vector <int>> matrix(h, std :: vector <int> (w, 0));
        for(std :: vector <int> & row: matrix) {
            for(int & number: row) {
                std :: cin >> number;
            }
        }
        std :: cout << compute_maximum_path_cost(matrix, h, w) << NEW_LINE;
    }
    return 0;
}

static int compute_maximum_path_cost(const std :: vector <std :: vector <int>> & matrix, const int h, const int w) {
    if(h == 1 && w == 1) {
        return matrix[0][0];
    }
    if(h == 1) {
        return *std :: max_element(matrix[0].begin(), matrix[0].end());
    }
    if(w == 1) {
        int sum_path = 0;
        for(int i = 0; i < h; ++i) {
            sum_path += matrix[i][0];
        }
        return sum_path;
    }
    std :: vector <int> cost_matrix(w, 0), temp_matrix(w, 0);
    for(int j = 0; j < w; ++j) {
        cost_matrix.at(j) = matrix[0][j];
    }
    for(int i = 1; i < h; ++i) {
        for(int j = 0; j < w; ++j) {
            if(!j) {
                temp_matrix.at(j) = std :: max(matrix[i][j] + cost_matrix.at(j), matrix[i][j] + cost_matrix.at(j + 1));
                continue;
            }
            if(j == (w - 1)) {
                temp_matrix.at(j) = std :: max(matrix[i][j] + cost_matrix.at(j), matrix[i][j] + cost_matrix.at(j - 1));
                continue;
            }
            temp_matrix.at(j) = std :: max(std :: max(matrix[i][j] + cost_matrix.at(j - 1), matrix[i][j] + cost_matrix.at(j)), matrix[i][j] + cost_matrix.at(j + 1));
        }
        for(int j = 0; j < w; ++j) {
            cost_matrix.at(j) = temp_matrix.at(j);
        }
    }
    return *std :: max_element(cost_matrix.begin(), cost_matrix.end());
}
