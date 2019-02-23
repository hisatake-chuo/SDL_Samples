#ifndef TEST001_SOUNDTEST_HPP
#define TEST001_SOUNDTEST_HPP


#include <SDL_mixer.h>
#include <string>

class SoundTest {
    Mix_Chunk *wave;
public:
    SoundTest(std::string fname);
    SoundTest();
    ~SoundTest();
    void load(std::string fname);
    void ring();
};


#endif //TEST001_SOUNDTEST_HPP
