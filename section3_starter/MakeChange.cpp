/*
 * CS106B Section Handout Test Harness: Section 3
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified for Qt and Ed by Neel
 * Kishnani for Winter 2022.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include <iostream>
#include <string>
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
#include "set.h"
#include <limits>
using namespace std;

/*
 * Function: fewestCoinsFor
 * -------------------------
 * Write a function that takes as input a number of cents and a Set<int>
 * indicating the different denominations of coins used in a country,
 * then returns the minimum number of coins required to make change
 * for that total. In the case of US coins, this should always return
 * the same number as the greedy approach, but in general it might return
 * a lot fewer!
 */
int fewestCoinsForHelper(int left, Vector<int> &coins, int index, int coinsCount) {
    if (index == coins.size() - 1) {
        int leftCoin = coins[index];
        if (left % leftCoin == 0) {
            return coinsCount + left / leftCoin;
        } else {
            return -1;
        }
    }

    int thisCoin = coins[index];
    int min = numeric_limits<int>::max();
    for (int i = 0; i * thisCoin <= left; i++) {
        int roundMin = fewestCoinsForHelper(left - i * thisCoin, coins, index + 1, coinsCount + i);
        if (roundMin != -1 && roundMin < min) {
            min = roundMin;
        }
    }
    return min;
}

int fewestCoinsFor(int cents, const Set<int>& coins) {
    Vector<int> sortedCoins;
    for (int coin : coins) {
        sortedCoins.add(coin);
    }
    sortedCoins.sort();
    return fewestCoinsForHelper(cents, sortedCoins, 0, 0);
}

/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Provided Test: Verify that the solution works on a simple example and the provided example") {
    Set<int> coins = {50, 25, 10, 5, 1};
    EXPECT_EQUAL(fewestCoinsFor(12, coins), 3);
    // You might want to uncomment this after implementing memoization.
    // EXPECT_EQUAL(fewestCoinsFor(97, coins), 6);
}
