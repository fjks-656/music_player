#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <stddef.h>

// 歌曲
typedef struct
{
    int id;
    char title[128];          // 歌名
    char artist[128];         // 作者
    char path[512];           // 文件路径
    float music_length;       // 歌曲时长，单位秒
    int player_count;         // 播放次数
    float feature_vector[16]; // 特征向量（16维）
} Song;

// 音乐库
typedef struct
{
    Song *songs;
    size_t size;
    size_t capacity;
} MusicLibrary;

// 播放集
typedef struct
{
    int id;
    char name[512];
    int *list; // 歌曲id数组
    size_t size;
} PlayingGollection;

/*
 * @brief 将歌曲导入，创建song对象，由library维护，统一由id查询
 * @note id由library分配，播放次数重置为零，特征向量调用analyzer分析
 * @warning 确保id唯一,且为正整数
 */
void ImportSong(const char *title, const char *artist, const char *path, float music_length);

// @brief 通过id删除歌曲
// @warning 需要将歌曲从所有播放集中删除，若正在播放该歌曲，则暂停并切换为下一首歌
void DeteleSong(int id);

// @brief 通过id查询歌曲
// @waring 返回的song指针之后可能失效，每次使用现查
const Song *GetSongById(int id);

/*
 * @brief 根据用户输入搜索歌曲列表
 * @note 可以通过歌名，歌手匹配，与playlist中的查询逻辑相同
 * @return 返回符合条件的歌曲id数组, 大小通过size回传
 */
int *SreachSong(size_t *size, const char *text);

// @brief 创建播放集
// @note 歌曲id数组大小可以给大点，不再动态扩容
// @note 播放集id与歌曲id同理
void CreatePlayCollection(const char *name);

// @brief 通过id删除播放集
// @note 若playlist正在播放该播放集，则将其更换为-1
void DeletePlayCollection(int id);

// @breif 获取所有播放集
const PlayingGollection *GetPlayingGollection(size_t *size);

// @brief 根据id获取播放集指针
const PlayingGollection *GetPlayingGollectionById(int id);

// @brief 通过歌曲id添加歌曲到对应id的播放集
void AddSongToPlayCollection(int song_id, int collection_id);

// @brief 通过歌曲id删除歌曲
void DeleteSongToPlayCollection(int song_id, int collection_id);

// @brief 通过歌曲id将播放顺序提升/下降
// @param order ture 升序 false 降序
void ChangePlayOrder(int song_id, int collection_id,bool order)
#endif