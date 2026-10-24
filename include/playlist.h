#ifndef _PLAYLIST_H_
#include "library.h"
#define _PLAYLIST_H_

/*
 * @brief 获取歌单数组
 * @param size 回传数组大小的指针
 * @return 歌单数组
 */
Song *get_playlist(size_t *size);

#endif