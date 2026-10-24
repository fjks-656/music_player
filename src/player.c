#include "player.h"

static bool is_playing = false;

bool GetIsPlaying(){
    return is_playing;
}


void SwitchPlaying(bool b){
    is_playing = b;
}