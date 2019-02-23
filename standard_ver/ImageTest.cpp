#include "ImageTest.hpp"

ImageTest::ImageTest(SDL_Renderer *_render, std::string fname) {
    render = _render;
    load(fname);
}

ImageTest::~ImageTest() {
    SDL_DestroyTexture(texture_img);
}

void ImageTest::load(std::string fname) {
    rw = SDL_RWFromFile(fname.c_str(), "rb");
    surface_img = IMG_LoadPNG_RW(rw);
    texture_img = SDL_CreateTextureFromSurface(render, surface_img);
    SDL_FreeSurface(surface_img);
    SDL_QueryTexture(texture_img, nullptr, nullptr, &iw, &ih);
}

void ImageTest::draw(int pos_x, int pos_y, int scale_x, int scale_y, SDL_Rect *img_paste) {
    SDL_Rect img_rect = (SDL_Rect){pos_x<iw ? pos_x:0,
                                   pos_y<ih ? pos_y:0,
                                   (iw-pos_x)>scale_x ? scale_x:(iw-pos_x),
                                   (ih-pos_y)>scale_y ? scale_y:(ih-pos_y)};
    SDL_RenderCopy(render, texture_img, &img_rect, img_paste);
}

ImageTest::ImageTest() {

}
