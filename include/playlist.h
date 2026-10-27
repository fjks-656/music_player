#ifndef _PLAYLIST_H_
#include "library.h"
#define _PLAYLIST_H_

/*
 * @brief 获取当前歌单数组
 * @note 如果当前未选择播放集，应根据相似度自行排列歌单
 * @param size 回传数组大小的指针
 * @return 歌单数组
 */
int *GetPlaylist(size_t *size);

/*
 * @brief 设置当前的播放集
 * @param id如果为-1则为未选择播放集
 * @note 当前选择的播放集应由本模块存储
 * @note 当前播放位置应更新
*/
void SetPlayCollection(int id);

// @brief 获取当前选择的播放集
int GetPlayCollectionNow();

// @breif 更新
// @note 每次循环调用,可以在这里排列歌单
void UpdatePlayList();

// @breif 将当前歌曲切换为下一首
// @note 当前播放歌曲由本模块存储
// @note 当来到playlist末端时要切换回第一首
// @return 切换后歌曲id
int NextSong();

// @breif 切换成上一首歌曲，与NextSong同理
// @waring 用户不一定按照歌曲顺序播放，可以建一个链表存储对应的id
int PrevSong();

// @breif 根据歌曲id切换当前播放的歌
// @note 确保id在当前播放集内
void SetPlayingSong(int id);

#endif