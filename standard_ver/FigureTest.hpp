#ifndef TEST001_FIGURETEST_HPP
#define TEST001_FIGURETEST_HPP
#include <SDL.h>

class FigureTest {
    SDL_Renderer *render;
public:
    FigureTest();
    explicit FigureTest(SDL_Renderer *_render);
    void drawTriangle(int ax, int ay, int bx, int by, int cx, int cy);
    void fillTriangle(int ax, int ay, int bx, int by, int cx, int cy);
    void drawOval(int _x, int _y, int rx, int ry);
    void fillOval(int _x, int _y, int rx, int ry);
    int calc_ovalY(int _x, int a, int b);
    inline int max(int x, int y, int z) {
        if (x > y) {
            if (x > z) {
                return x;
            } else {
                return z;
            }
        } else {
            if (y > z) {
                return y;
            } else {
                return z;
            }
        }
    }
    inline int min(int x, int y, int z) {
        if (x < y) {
            if (x < z) {
                return x;
            } else {
                return z;
            }
        } else {
            if (y < z) {
                return y;
            } else {
                return z;
            }
        }
    }
    inline int mid(int x, int y, int z) {
        if (x > y) {
            if (x > z) {
                if (y > z) {
                    return y;
                } else {
                    return z;
                }
            } else {
                return x;
            }
        } else {
            if (y > z) {
                if (x > z) {
                    return x;
                } else {
                    return y;
                }
            } else {
                return y;
            }
        }
    }

};


#endif //TEST001_FIGURETEST_HPP
