#ifndef TEST001_SDLTEST_HPP
#define TEST001_SDLTEST_HPP


#include "ImageTest.hpp"
#include "FigureTest.hpp"
#include "SoundTest.hpp"
#include "TextTest.hpp"

class SDLTest {
    SDL_Window *window;
    SDL_Renderer *render;
    SDL_Event ev;
    SDL_Rect rect;
    ImageTest *img;
    SoundTest *sound;
    FigureTest *figure;
    TextTest *text;

public:
    SDLTest();
    ~SDLTest();
    int init();
    void mainCall(int _fps);
};


#endif //TEST001_SDLTEST_HPP
