#include "TextTest.hpp"

TextTest::TextTest(SDL_Renderer *_render){
    TTF_Init();
    render = _render;
    font = TTF_OpenFont("ipag.ttf", 30);
    green = {0, 255, 0, 255};
}

TextTest::~TextTest() {
    SDL_DestroyTexture(texture_ttf);
    TTF_CloseFont(font);
    TTF_Quit();
}

void TextTest::drawText(int x, int y, std::string str) {
    surface_ttf = TTF_RenderUTF8_Blended(font, str.c_str(), green);
    texture_ttf = SDL_CreateTextureFromSurface(render, surface_ttf);
    SDL_FreeSurface(surface_ttf);
    int iw,ih;
    SDL_QueryTexture(texture_ttf, nullptr, nullptr, &iw, &ih);
    SDL_Rect txt_rect = (SDL_Rect){0, 0, iw, ih};
    SDL_Rect txt_paste = (SDL_Rect){x, y, iw, ih};
    SDL_RenderCopy(render, texture_ttf, &txt_rect, &txt_paste);
}

TextTest::TextTest() {

}
