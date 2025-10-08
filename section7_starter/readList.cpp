/*
 * CS106B Section Handout Test Harness: Section 7
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified by Neel Kishnani for 
 * Winter 2022.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */
#include <iostream>
#include <string>
#include "testing/SimpleTest.h"
#include "error.h"
using namespace std;

/*
 * Struct definition to store string as value instead of int version
 * in cell.h
 */
struct Cell {
    string value;
    Cell *next;
};

/*
 * Function: readList
 * -------------------
 * Prompts the user 
 */
Cell* readList() {
    return nullptr;
}

/* * * * * Add any additional STUDENT_TESTS here * * * * */

// Note: no PROVIDED_TESTs since output relies on user interaction
