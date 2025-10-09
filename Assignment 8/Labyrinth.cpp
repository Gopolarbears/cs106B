#include "Labyrinth.h"
using namespace std;

void tryFind(bool& findSpellBook, bool& findPotion, bool& findWand, MazeCell*& cur) {
    if (cur->whatsHere == Item::SPELLBOOK) {
        findSpellBook = true;
    } else if (cur->whatsHere == Item::POTION) {
        findPotion = true;
    } else if (cur->whatsHere == Item::WAND) {
        findWand = true;
    }
}

bool isPathToFreedom(MazeCell* start, const string& moves) {
    bool findSpellBook = false;
    bool findPotion = false;
    bool findWand = false;
    MazeCell* cur = start;
    tryFind(findSpellBook, findPotion, findWand, cur);
    for (char move : moves) {
        if (move == 'N') {
            if (cur->north == nullptr) {
                return false;
            }
            cur = cur->north;
        } else if (move == 'S') {
            if (cur->south == nullptr) {
                return false;
            }
            cur = cur->south;
        }
        if (move == 'W') {
            if (cur->west == nullptr) {
                return false;
            }
            cur = cur->west;
        }
        if (move == 'E') {
            if (cur->east == nullptr) {
                return false;
            }
            cur = cur->east;
        }
        tryFind(findSpellBook, findPotion, findWand, cur);
    }
    return findSpellBook && findPotion && findWand;
}


/* * * * * * Test Cases Below This Point * * * * * */
#include "GUI/SimpleTest.h"
#include "Demos/MazeGenerator.h"

/* Optional: Add your own custom tests here! */














/* * * * * Provided Tests Below This Point * * * * */

/* Utility function to free all memory allocated for a maze. */
void deleteMaze(const Grid<MazeCell*>& maze) {
    for (auto* elem: maze) {
        delete elem;
    }
    /* Good question to ponder: why don't we write 'delete maze;'
     * rather than what's shown above?
     */
}

PROVIDED_TEST("Checks paths in the sample maze.") {
    auto maze = toMaze({"* *-W *",
                        "| |   |",
                        "*-* * *",
                        "  | | |",
                        "S *-*-*",
                        "|   | |",
                        "*-*-* P"});

    /* These paths are the ones in the handout. They all work. */
    EXPECT(isPathToFreedom(maze[2][2], "ESNWWNNEWSSESWWN"));
    EXPECT(isPathToFreedom(maze[2][2], "SWWNSEENWNNEWSSEES"));
    EXPECT(isPathToFreedom(maze[2][2], "WNNEWSSESWWNSEENES"));

    /* These paths don't work, since they don't pick up all items. */
    EXPECT(!isPathToFreedom(maze[2][2], "ESNW"));
    EXPECT(!isPathToFreedom(maze[2][2], "SWWN"));
    EXPECT(!isPathToFreedom(maze[2][2], "WNNE"));

    /* These paths don't work, since they aren't legal paths. */
    EXPECT(!isPathToFreedom(maze[2][2], "WW"));
    EXPECT(!isPathToFreedom(maze[2][2], "NN"));
    EXPECT(!isPathToFreedom(maze[2][2], "EE"));
    EXPECT(!isPathToFreedom(maze[2][2], "SS"));

    deleteMaze(maze);
}

PROVIDED_TEST("Can't walk through walls.") {
    auto maze = toMaze({"* S *",
                        "     ",
                        "W * P",
                        "     ",
                        "* * *"});

    EXPECT(!isPathToFreedom(maze[1][1], "WNEES"));
    EXPECT(!isPathToFreedom(maze[1][1], "NWSEE"));
    EXPECT(!isPathToFreedom(maze[1][1], "ENWWS"));
    EXPECT(!isPathToFreedom(maze[1][1], "SWNNEES"));

    deleteMaze(maze);
}

PROVIDED_TEST("Works when starting on an item.") {
    auto maze = toMaze({"P-S-W"});

    EXPECT(isPathToFreedom(maze[0][0], "EE"));
    EXPECT(isPathToFreedom(maze[0][1], "WEE"));
    EXPECT(isPathToFreedom(maze[0][2], "WW"));

    deleteMaze(maze);
}

