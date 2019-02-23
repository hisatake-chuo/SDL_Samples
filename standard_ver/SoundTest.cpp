#include "SoundTest.hpp"

SoundTest::SoundTest(std::string fname) {
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    load(fname);
}

SoundTest::~SoundTest() {
    Mix_FreeChunk(wave);
    Mix_CloseAudio();
}

void SoundTest::load(std::string fname) {
    wave = Mix_LoadWAV(fname.c_str());
}

void SoundTest::ring() {
    Mix_PlayChannel(-1, wave, 0);
}

SoundTest::SoundTest() {

}


