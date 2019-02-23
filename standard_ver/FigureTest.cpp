#include <cmath>
#include "FigureTest.hpp"

FigureTest::FigureTest(SDL_Renderer *_render) {
    render = _render;
}

FigureTest::FigureTest() {

}

void FigureTest::drawTriangle(int ax, int ay, int bx, int by, int cx, int cy) {
    SDL_RenderDrawLine(render, ax, ay, bx, by);
    SDL_RenderDrawLine(render, bx, by, cx, cy);
    SDL_RenderDrawLine(render, cx, cy, ax, ay);
}

void FigureTest::fillTriangle(int ax, int ay, int bx, int by, int cx, int cy) {
    if (ax == bx && bx == cx) {
        SDL_RenderDrawLine(render, ax, min(ay, by, cy), ax, max(ay, by, cy));
    } else if (ax == bx) {
        if (ax < cx) {
            for (int dx = 0; dx < cx - ax; dx++) {
                SDL_RenderDrawLine(render, ax+dx, ay+(cy-ay)*dx/(cx-ax), ax+dx, by+(cy-by)*dx/(cx-bx));
            }
        } else {
            for (int dx = 0; dx < ax - cx; dx++) {
                SDL_RenderDrawLine(render, cx+dx, cy+(cy-ay)*dx/(cx-ax), cx+dx, cy+(cy-by)*dx/(cx-bx));
            }
        }
    } else if (bx == cx) {
        fillTriangle(bx, by, cx, cy, ax, ay);
    } else if (ax == cx) {
        fillTriangle(cx, cy, ax, ay, bx, by);
    } else if (ax < cx && cx < bx) {
        fillTriangle(ax, ay, cx, cy, bx, by);
    } else if (bx < ax && ax < cx) {
        fillTriangle(bx, by, ax, ay, cx, cy);
    } else if (bx < cx && cx < ax) {
        fillTriangle(bx, by, cx, cy, ax, ay);
    } else if (cx < ax && ax < bx) {
        fillTriangle(cx, cy, ax, ay, bx, by);
    } else if (cx < bx && bx < ax) {
        fillTriangle(cx, cy, bx, by, ax, ay);
    } else { //ax < bx < cx
        fillTriangle(bx, by, bx, ay+(cy-ay)*(bx-ax)/(cx-ax), ax, ay);
        fillTriangle(bx, by, bx, ay+(cy-ay)*(bx-ax)/(cx-ax), cx, cy);
    }
}


void FigureTest::drawOval(int _x, int _y, int rx, int ry) {
    int n_points;
    if (rx < ry) {
        n_points = ry*8;
    } else {
        n_points = rx*8;
    }
    SDL_Point oval[n_points];

    for (int theta = 0; theta < n_points; theta++) {
        SDL_Point p;
        const double pi = 3.1415926;
        p.x = _x + rx + (int)(rx * std::cos(2*theta*pi/n_points));
        p.y = _y + ry + (int)(ry * std::sin(2*theta*pi/n_points));
        oval[theta] = p;
    }
    SDL_RenderDrawPoints(render, oval, n_points);
}

void FigureTest::fillOval(int _x, int _y, int rx, int ry) {
    for (int dx = 0; dx < rx * 2; dx++) {
        int above_x = _x + dx;
        int above_y = _y + ry + calc_ovalY(dx-rx, rx, ry);
        int below_x = _x + dx;
        int below_y = _y + ry - calc_ovalY(dx-rx, rx, ry);
        SDL_RenderDrawLine(render, above_x, above_y, below_x, below_y);
    }
}

int FigureTest::calc_ovalY(int _x, int a, int b) {
    return (int)(std::sqrt(a*a*b*b - b*b*_x*_x + 0.0)/a);
}


