#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <stdbool.h>

// @return 歌曲是否播放
bool GetIsPlaying();

// @brief 切换歌曲播放状态
// @param is_playing 是否在播放
void SwitchPlaying(bool is_playing);

#endif