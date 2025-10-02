/* File: OnlyConnect.cpp
 *
 * TODO: Edit these comments to describe anything interesting or noteworthy in your implementation.
 *
 * TODO: Edit these comments to leave a puzzle for your section leader to solve!
 */
#include "OnlyConnect.h"
#include "GUI/SimpleTest.h"
#include "set.h"
#include <cctype>
#include "strlib.h"
using namespace std;

string onlyConnectizeHelper(string &phrase, int index, Set<char> &vowels) {
    if (index == phrase.size()) {
        return "";
    }

    char ch = phrase[index];
    if (isalpha(ch) && !vowels.contains(ch)) {
        return toUpperCase(ch) + onlyConnectizeHelper(phrase, index + 1, vowels);
    } else {
        return onlyConnectizeHelper(phrase, index + 1, vowels);
    }
}

string onlyConnectize(string phrase) {
    Set<char> vowels;
    vowels.add('a');
    vowels.add('e');
    vowels.add('i');
    vowels.add('o');
    vowels.add('u');
    vowels.add('A');
    vowels.add('E');
    vowels.add('I');
    vowels.add('O');
    vowels.add('U');
    return onlyConnectizeHelper(phrase, 0, vowels);
}

/* * * * * * Provided Test Cases * * * * * */

PROVIDED_TEST("Converts lower-case to upper-case.") {
    EXPECT_EQUAL(onlyConnectize("lowercase"), "LWRCS");
    EXPECT_EQUAL(onlyConnectize("uppercase"), "PPRCS");
}

PROVIDED_TEST("Handles non-letter characters properly.") {
    EXPECT_EQUAL(onlyConnectize("2.718281828459045"), "");
    EXPECT_EQUAL(onlyConnectize("'Hi, Mom!'"), "HMM");
}

PROVIDED_TEST("Handles single-character inputs.") {
    EXPECT_EQUAL(onlyConnectize("A"), "");
    EXPECT_EQUAL(onlyConnectize("+"), "");
    EXPECT_EQUAL(onlyConnectize("Q"), "Q");
}

STUDENT_TEST("Handles letter-nonLetter characters preperly") {
    EXPECT_EQUAL(onlyConnectize("2.71828lowercase1828459045"), "LWRCS");
    EXPECT_EQUAL(onlyConnectize("'Hi, Mom!PPRCS'"), "HMMPPRCS");
}

/* TODO: You will need to add your own tests into this suite of test cases. Think about the sorts
 * of inputs we tested here, and, importantly, what sorts of inputs we *didn't* test here. Some
 * general rules of testing:
 *
 *    1. Try extreme cases. What are some very large cases to check? What are some very small cases?
 *
 *    2. Be diverse. There are a lot of possible inputs out there. Make sure you have tests that account
 *       for cases that aren't just variations of one another.
 *
 *    3. Be sneaky. Don't just try standard inputs. Try weird ones that you wouldn't expect anyone to
 *       actually enter, but which are still perfectly legal.
 *
 * Happy testing!
 */






