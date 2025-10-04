/*
 * CS106B Section Handout Test Harness: Section 4
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
#include "map.h"
#include <cmath>
using namespace std;

/*
 * Function: canVisitAllSites
 * ---------------------------
 * Write a function that takes as input a list of all the
 * sites you’d like to visit and an amount of free time
 * available to you and returns whether it’s possible to
 * visit all those sites in the allotted time (assume you’ve
 * already factored inthe cost of speaking at each site
 * and that you’re just concerned about the travel time.)
 */
double computeDistance(const GPoint& pointA, const GPoint& pointB) {
    return sqrt(pow(abs(pointA.x - pointB.x), 2) + pow(abs(pointA.y - pointB.y), 2));
}

bool canVisitAllSitesHelper(const Vector<GPoint>& sites, double travelTimeLeft, const Set<GPoint>& sitesVisited) {
    if (sitesVisited.size() == sites.size() && travelTimeLeft >= 0) {
        return true;
    }
    if (travelTimeLeft < 0) {
        return false;
    }

    for (GPoint site : sites) {
        if (sitesVisited.contains(site)) {
            continue;
        }
        if (sitesVisited.isEmpty()) {
            if (canVisitAllSitesHelper(sites, travelTimeLeft, sitesVisited + site)) {
                return true;
            }
        } else {
            if (canVisitAllSitesHelper(sites, travelTimeLeft - computeDistance(site, sitesVisited.last()), sitesVisited + site)) {
                return true;
            }
        }
    }
    return false;
}

bool canVisitAllSites(const Vector<GPoint>& sites, double travelTimeAvailable) {
    Set<GPoint> sitesVisited;
    return canVisitAllSitesHelper(sites, travelTimeAvailable, sitesVisited);
}

/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Provided Test: Simple examples!") {
    Vector<GPoint> sites1 = {{0, 0}, {5, 5}};
    Vector<GPoint> sites2 = {{0, 0}, {2, 2}, {5, 5}};
    EXPECT_EQUAL(canVisitAllSites(sites1, 8), true);
    EXPECT_EQUAL(canVisitAllSites(sites2, 8), true);
}
