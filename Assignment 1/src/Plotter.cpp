#include "Plotter.h"
#include "strlib.h"
using namespace std;

void moveAbs(double &row, double &col, double targetRow, double targetCol, const PenStyle &style, bool isPenUp) {
    if (isPenUp) {
        row = targetRow;
        col = targetCol;
        return;
    }
    drawLine(row, col, targetRow, targetCol, style);
    row = targetRow;
    col = targetCol;
}

void moveRel(double &row, double &col, double relativeRow, double relativeCol, const PenStyle &style, bool isPenUp) {
    if (isPenUp) {
        row += relativeRow;
        col += relativeCol;
        return;
    }
    drawLine(row, col, row + relativeRow, col + relativeCol, style);
    row += relativeRow;
    col += relativeCol;
}

void runPlotterScript(istream& input) {
    bool isPenUp = true;
    PenStyle style = {1, "black"};
    double row = 0.0;
    double col = 0.0;

    for (string line; getline(input, line);) {
        line = toLowerCase(line);
        Vector<string> commands = stringSplit(line, " ");
        if (commands[0] == "pendown") {
            isPenUp = false;
        } else if (commands[0] == "penup") {
            isPenUp = true;
        } else if (commands[0] == "moveabs") {
            moveAbs(row, col, stringToDouble(commands[1]), stringToDouble(commands[2]), style, isPenUp);
        } else if (commands[0] == "moverel") {
            moveRel(row, col, stringToDouble(commands[1]), stringToDouble(commands[2]), style, isPenUp);
        } else if (commands[0] == "pencolor") {
            style.color = commands[1];
        } else if (commands[0] == "penwidth") {
            style.width = stringToDouble(commands[1]);
        }
    }
}




