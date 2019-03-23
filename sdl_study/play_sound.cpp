#include <iostream>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
#include "sdl2/SDL.h"
};

static Uint8 * audio_chunk;
static Uint32 audio_len;
static Uint8 * audio_pos;

void fill_audio(void * udata, Uint8 * stream, int len) {

    //SDL_memset(stream, 0, len);
    if (audio_len == 0) {
        return;
    }

    len = (len > audio_len ? audio_len : len);
    SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);
    audio_pos += len;
    audio_len -= len;
}

int main(int argc, char * * argv) {

    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " filename" << std::endl;
        return -1;
    }

    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        std::cout << "Could not initialize SDL " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_AudioSpec want;
    
    want.freq = 10500;
    want.format = AUDIO_S16SYS;
    want.channels = 2;
    want.silence = 0;
    want.samples = 1024;
    want.callback = fill_audio;

    if (SDL_OpenAudio(&want, NULL) < 0) {
        std::cout << "Can't open audio" << std::endl;
        return -1;
    }

    FILE * fp = fopen(argv[1], "rb+");
    if (!fp) {
        std::cout << "Can't open this file" << std::endl;
        return -1;
    }

    int buffer_size = 4096;
    char * buffer = (char *)malloc(buffer_size);
    if (!buffer) {
        std::cout << "new buffer failed" << std::endl;
        return -1;
    }    

    int data_count = 0;

    SDL_PauseAudio(0);

    while (1) {
        if (fread(buffer, 1, buffer_size, fp) != buffer_size) {
            fseek(fp, 0, SEEK_SET);
            fread(buffer, 1, buffer_size, fp);
            data_count = 0;
        }

        std::cout << "Now Playing " << data_count << " Bytes data" << std::endl;

        data_count += buffer_size;
        audio_chunk = (Uint8 *)buffer;

        audio_len = buffer_size;

        audio_pos = audio_chunk;

        while (audio_len > 0) {
            SDL_Delay(1);
        }
    }

    free(buffer);
    SDL_Quit();
    return 0;
}
