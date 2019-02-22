#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

int main() {
    //初期化
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);
    TTF_Init();
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );

    //必要な変数の宣言と定義
    SDL_Window *window = SDL_CreateWindow("SDL test", 150, 150, 480, 270, 0);
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, 0);
    TTF_Font *font = TTF_OpenFont("ipag.ttf", 30);
    SDL_Rect rect = {10, 10, 120, 50};
    SDL_Color green = {0, 255, 0, 255};
    SDL_Event ev;
    SDL_RWops *rw;
    SDL_Surface *surface_ttf;
    SDL_Texture *texture_ttf;
    SDL_Surface *surface_img;
    SDL_Texture *texture_img;
    Mix_Chunk *wave = Mix_LoadWAV("test.wav");
    std::string str = "test";
    int cnt1 = 0;
    int cnt2 = 0;
    int fps = 30;
    int real_fps = -1;
    
    while (true) {
        auto start = std::chrono::system_clock::now();

        //画面を初期化
        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderClear(render);
        //バツボタンで終了
        while(SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                TTF_CloseFont(font);
                SDL_DestroyRenderer(render);
                SDL_DestroyWindow(window);
                TTF_Quit();
                SDL_Quit();
                return 0;
            }
        }

        //四角い枠を描画(SDL標準)
        SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        SDL_RenderDrawRect(render, &rect);

        //fpsを計算して表示(SDL_ttf)
        if (real_fps >= 0) {
            str = "fps: " + std::to_string(real_fps);
        }
        surface_ttf = TTF_RenderUTF8_Blended(font, str.c_str(), green);
        texture_ttf = SDL_CreateTextureFromSurface(render, surface_ttf);
        SDL_FreeSurface(surface_ttf);
        int iw,ih;
        SDL_QueryTexture(texture_ttf, nullptr, nullptr, &iw, &ih);
        SDL_Rect txt_rect = (SDL_Rect){0, 0, iw, ih};
        SDL_Rect txt_paste = (SDL_Rect){20, 20, iw, ih};
        SDL_RenderCopy(render, texture_ttf, &txt_rect, &txt_paste);

        //画像を表示(SDL_image)
        rw = SDL_RWFromFile("test.png", "rb");
        surface_img = IMG_LoadPNG_RW(rw);
        texture_img = SDL_CreateTextureFromSurface(render, surface_img);
        SDL_FreeSurface(surface_img);
        SDL_QueryTexture(texture_img, nullptr, nullptr, &iw, &ih);
        //切り出す位置と大きさ
        int pos_x = 150;
        int pos_y = 150;
        int scale_x = 200;
        int scale_y= 200;
        SDL_Rect img_rect = (SDL_Rect){pos_x<iw ? pos_x:0,
                                       pos_y<ih ? pos_y:0,
                                       (iw-pos_x)>scale_x ? scale_x:(iw-pos_x),
                                       (ih-pos_y)>scale_y ? scale_y:(ih-pos_y)};
        //貼り付ける位置と大きさ
        SDL_Rect img_paste = (SDL_Rect){20, 60, 200, 200};
        SDL_RenderCopy(render, texture_img, &img_rect, &img_paste);

        //描画命令を纏めて実行
        SDL_RenderPresent(render);

        //繰り返し音をだす(SDL_mixer)
        if (cnt1+1 > fps) {
            Mix_PlayChannel(-1, wave, 0);
        }

        //fpsを安定させるための処理
        cnt1++;
        cnt2++;
        int adjustment = 0;
        int adjust_cycle = fps / (1000 - (1000/fps)*fps);
        if (cnt2 > adjust_cycle) {
            cnt2 = 0;
            adjustment += 1;
        }
        if (cnt1 > fps) {
            cnt1 = 0;
            int tmp  = 1000 - (1000/fps)*fps - adjust_cycle;
            adjustment += tmp > 0 ? tmp : 0;
        }
        auto end = std::chrono::system_clock::now();
        auto leaped = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        int sleep_time = ((1000 / fps) - (int)leaped + adjustment);
        if (sleep_time > 0) {
            SDL_Delay((Uint32)sleep_time);
        }
        real_fps = 1000/(sleep_time + (int)leaped);
    }


    return 0;
}
