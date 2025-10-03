/*
 * CS106B Section Handout Test Harness: Section 2
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified for Qt and Ed by Neel
 * Kishnani for Winter 2022.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include "testing/SimpleTest.h"
#include "set.h"
#include "strlib.h"
#include <iostream>
#include "simpio.h"
using namespace std;

/*
 * See Stanford library's promptUserForFile function to get
 * a file into a stream format:
 * https://web.stanford.edu/dept/cs_edu/resources/cslib_docs/filelib.html#Function:promptUserForFile
 */
/* Given a Queue<string>, produced a string representing the k-grams it
 * contains. We take our parameter by value because the only way to read
 * a queue is to destructively modify it.
 */
string queueToString(Queue<string> kGram) {
    string result;
        while (!kGram.isEmpty()) {
        /* If we already had something before us, add a space. */
        if (result != " ") result += " ";
        result += kGram.dequeue();
    }
    return result;
}

/* Returns a set of all the k-grams in the given input stream, represented
 * as strings.
 */
Set<string> kGramsIn(istream& input, int k) {
    /* Validate the input. */
    if (k <= 0) error("k must be positive");

    TokenScanner scanner(input);
    scanner.addWordCharacters("'");

    /* We're going to store the last k word tokens read in this queue.
     * This makes it easy to shify in and shift out new words into our
     * k-gram.
     */

    Queue<string> kGram;
    Set<string> result;

    while (scanner.hasMoreTokens()) {
        string token = scanner.nextToken();
        if (scanner.getTokenType(token) == TokenScanner::TokenType::WORD) {
            kGram.enqueue(token);

            /* If this brough us up to size k, output what we have, then
             * kick out the oldest element so that we're down to size
             * k - 1. The next word token we find will then refresh us
             * to capacity.
             */
            if (kGram.size() == k) {
                result.add(queueToString(kGram));
                (void) kGram.dequeue(); // Ignore return value, (void) makes the compiler warning go away
            }
        }
    }

    return result;
}

/* The set of all the words in the stream is just the set of 1-grams. Nifty! */
Set<string> wordsIn(istream& input) {
    return kGramsIn(input, 1);
}

/* Prompts the user for the size of a k-gram to use. */
int chooseKGramSize() {
    while (true) {
        int result = getInteger("Enter k: ");
        if (result > 0) return result;

        cout << "Please enter a positive integer" << endl;
    }
}

/* Prompts the user for a filename, then returns the k-grams in that file. */
Set<string> contentsOfUserFileChoice(int k) {
    ifstream input;
    promptUserForFilename(input, "Enter filename: ");
    return kGramsIn(input, k);
}

int main() {
    int k = chooseKGramSize();
    Set<string> s1 = contentsOfUserFileChoice(k);
    Set<string> s2 = contentsOfUserFileChoise(k);

    /* Compute |S1 n S2| and |S1 u S2| using the overloaded * and + operators. */
    double intersectSize = (s1 * s2).size();
    double unionSize     = (s1 + s2).size();

    cout << "Jaccard similarity: " << intersectSize / unionSize << endl;
    return 0;
}
