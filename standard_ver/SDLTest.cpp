#include <iostream>
#include "SDLTest.hpp"

SDLTest::SDLTest() {
    init();
    window = SDL_CreateWindow("SDL test", 150, 150, 640, 360, 0);
    render = SDL_CreateRenderer(window, -1, 0);
    rect = {10, 10, 120, 50};

    std::string image_file_name = "test.png";
    img = new ImageTest(render, image_file_name);
    std::string audio_file_name = "test.wav";
    sound = new SoundTest(audio_file_name);
    figure = new FigureTest(render);
    text = new TextTest(render);
}

SDLTest::~SDLTest() {
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    delete &img;
    delete &figure;
    delete &text;
    delete &sound;
}

int SDLTest::init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        return -1;
    }
    return 0;
}

void SDLTest::mainCall(int _fps) {
    int cnt1 = 0;
    int cnt2 = 0;
    int fps = _fps;
    int real_fps = -1;
    std::string str = "dummy";

    while (true) {
        auto start = std::chrono::system_clock::now();

        //画面を初期化
        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderClear(render);
        //バツボタンで終了
        while(SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                exit(0);
            }
        }

        //四角い枠を描画(SDL標準)
        SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        SDL_RenderDrawRect(render, &rect);

        //fpsを計算して表示(SDL_ttf)
        if (real_fps >= 0) {
            str = "fps: " + std::to_string(real_fps);
        }
        text->drawText(20, 20, str);

        //画像を表示(SDL_image)
        //切り出す位置と大きさを指定
        int pos_x = 150;
        int pos_y = 150;
        int scale_x = 200;
        int scale_y= 200;
        //貼り付ける位置と大きさ
        SDL_Rect img_paste = (SDL_Rect){20, 60, 200, 200};
        img->draw(pos_x, pos_y, scale_x, scale_y, &img_paste);

        //図形を表示
        SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
        figure->fillTriangle(300, 100, 600, 200, 400, 300);
        SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        figure->drawOval(120-cnt1*10/3, 160-cnt1*10/3, 10+cnt1*3, 10+cnt1*3);

        //描画命令を纏めて実行
        SDL_RenderPresent(render);

        //繰り返し音をだす(SDL_mixer)
        if (cnt1+1 > fps) {
            sound->ring();
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

}

