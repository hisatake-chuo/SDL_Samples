#ifndef TEST001_IMAGETEST_HPP
#define TEST001_IMAGETEST_HPP
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class ImageTest {
    SDL_Renderer *render;
    SDL_RWops *rw;
    SDL_Surface *surface_img;
    SDL_Texture *texture_img;
    int iw;
    int ih;

public :
    ImageTest();
    ImageTest(SDL_Renderer *_render, std::string fname);
    ~ImageTest();
    void load(std::string fname);
    void draw(int pos_x, int pos_y, int scale_x, int scale_y, SDL_Rect *img_paste);
};


#endif //TEST001_IMAGETEST_HPP
