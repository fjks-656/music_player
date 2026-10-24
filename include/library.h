#include <stddef.h>

// 歌曲时长
typedef struct
{
    int minutes;
    int seconds;
} SongDuration;

// 歌曲
typedef struct
{
    int id;
    char title[128];          // 歌名
    char artist[128];         // 作者
    char path[512];           // 文件路径
    SongDuration music_length; // 歌曲时长
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
    Song **list; //歌曲指针数组
    size_t size;
} PlayingGollection;

