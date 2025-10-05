#include "Sierpinski.h"
#include "error.h"
using namespace std;

/**
 * Draws a triangle with the specified corners in the specified window. Feel free
 * to edit this function as you see fit to change things like color, fill style,
 * etc. in whatever way you'd like!
 *
 * @param window The window in which to draw the triangle.
 * @param x0 y0 The first corner of the triangle.
 * @param x1 y1 The second corner of the triangle.
 * @param x2 y2 The third corner of the triangle.
 */
void drawTriangle(GWindow& window,
                  double x0, double y0,
                  double x1, double y1,
                  double x2, double y2) {
    window.setColor("black");
    window.fillPolygon({ x0, y0, x1, y1, x2, y2 });
}

/* TODO: Refer to Sierpinski.h for more information about what this function should do.
 * Then, delete this comment.
 */
void drawSierpinskiTriangle(GWindow& window,
                            double x0, double y0,
                            double x1, double y1,
                            double x2, double y2,
                            int order) {
    if (order < 0) {
        error("Order shoule be none-negative");
    }
    if (order == 0) {
        drawTriangle(window, x0, y0, x1, y1, x2, y2);
        return;
    }
    double x3 = (x0 + x1) / 2.0;
    double y3 = (y0 + y1) / 2.0;
    double x4 = (x0 + x2) / 2.0;
    double y4 = (y0 + y2) / 2.0;
    double x5 = (x1 + x2) / 2.0;
    double y5 = (y1 + y2) / 2.0;
    drawSierpinskiTriangle(window, x0, y0, x3, y3, x4, y4, order - 1);
    drawSierpinskiTriangle(window, x3, y3, x1, y1, x5, y5, order - 1);
    drawSierpinskiTriangle(window, x4, y4, x5, y5, x2, y2, order - 1);

}
