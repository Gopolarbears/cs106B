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
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
#include "set.h"
#include "error.h"
using namespace std;

/*
 * Function: listPossiblePayments
 * -------------------------------
 * Write a function that takes as input a total amount of money
 * to pay (in dollars) and a set of all the people who ordered
 * something, then lists off every possible way you could split
 * the bill, assuming everyone pays a whole number of dollars.
 */
void printBills(const Map<string, int> &peopleAndBills) {
    cout << endl;
    for (string people : peopleAndBills.keys()) {
        cout << people << ": $" << peopleAndBills.get(people) << "    ";
    }
}

void listPossiblePaymentsHelper(int left, const Map<string, int> &peopleAndBills, const Set<string> &people) {
    if (people.size() == 1) {
        Map<string, int> newPeopleAndBills = peopleAndBills;
        newPeopleAndBills.put(people.first(), left);
        printBills(newPeopleAndBills);
        return;
    }

    for (int i = 0; i <= left; i++) {
        Map<string, int> newPeopleAndBills = peopleAndBills;
        newPeopleAndBills.put(people.first(), i);
        listPossiblePaymentsHelper(left - i, newPeopleAndBills, people - people.first());
    }
}

void listPossiblePayments(int total, const Set<string>& people) {
    if (total < 0) {
        error("Total should be positive");
    }
    if (people.isEmpty()) {
        error("There should be at least one person");
    }
    Map<string, int> peopleAndBills;
    listPossiblePaymentsHelper(total, peopleAndBills, people);
}

void listPossiblePaymentsHelper2(int left, Map<string, int> &peopleAndBills, Set<string> &people) {
    if (people.size() == 1) {
        peopleAndBills.put(people.first(), left);
        printBills(peopleAndBills);
        peopleAndBills.remove(people.first());
        return;
    }

    for (int i = 0; i <= left; i++) {
        string first = people.first();
        peopleAndBills.put(first, i);
        people.remove(first);
        listPossiblePaymentsHelper(left - i, peopleAndBills, people);
        peopleAndBills.remove(first);
        people.add(first);
    }
}

void listPossiblePayments2(int total, Set<string>& people) {
    if (total < 0) {
        error("Total should be positive");
    }
    if (people.isEmpty()) {
        error("There should be at least one person");
    }
    Map<string, int> peopleAndBills;
    listPossiblePaymentsHelper2(total, peopleAndBills, people);
}

/* * * * * Provided Tests Below This Point * * * * */

/*
 * Since this is a void function, we don't have a return value to verify with.
 * We will instead just run your code to make sure there is no obvious error.
 */
PROVIDED_TEST("Provided Test: Run the provided example. There should be 15 entries.") {
    Set<string> s = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "G", "K", "L", "M", "N"};
    // listPossiblePayments2(4, s);
    TIME_OPERATION(14, listPossiblePayments2(4, s));
    TIME_OPERATION(14, listPossiblePayments(4, s));
}
