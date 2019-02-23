#ifndef TEST001_TEXTTEST_HPP
#define TEST001_TEXTTEST_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class TextTest {
    SDL_Renderer *render;
    TTF_Font *font;
    SDL_Surface *surface_ttf;
    SDL_Texture *texture_ttf;
    SDL_Color green;
public:
    TextTest();
    ~TextTest();
    explicit TextTest(SDL_Renderer *_render);
    void drawText(int x, int y,std::string str);
};


#endif //TEST001_TEXTTEST_HPP
