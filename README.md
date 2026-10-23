# Music Player
## 一.概述
### 1.1简介
    制作一个简洁，优美，具有一定实用价值的本地音乐播放器
### 1.2 技术栈
- 语言     C23
- 图形界面 raylib 
- 音频播放 raylib Audio
- 构建工具 make
- 开发环境 vscode + MinGw-w64
- 版本管理 git+github
## 二.功能需求
### 2.1 音乐播放模块
- 加载索引库中的音乐
- 播放，暂停，拖动进度条
- 根据歌单顺序连播或单曲循环
### 2.2 音乐库模块
- 导入本地歌曲，支持文件夹导入
- 建立歌曲文件地址索引库
- 支持搜索，删除，查找歌曲
- 记录歌曲的播放次数
### 2.3 音乐分析模块
- 分析音乐的节奏风格，生成特征向量
- 通过特征和播放次数排列播放顺序快
- 速傅里叶变换生成以供可视化
### 2.4 gui模块
- 见ui设计稿

## 三.架构设计
```
MusicPlayer/
│
├── .data/          存储索引库
├── build/          存储.exe和.o
├── lib/            
│   └── raylib.a ...
│
├── src/
│   ├── main.c
│   ├── player.c
│   ├── library.c
│   ├── analyzer.c
│   ├── playlist.c
│   └── ui.c
│
├── include/
│   ├── player.h
│   ├── library.h
│   ├── analyzer.h
│   ├── playlist.h
│   ├── ui.h
│   └── raylib.h ...
│
├── assets/ 
├── Makefile
├── .gitignore
└── README.md
```
1. main
    - 创建程序运行主循环，调用player模块，analyzer模块，ui模块对应的update函数，传入时间戳timetick
    - 调用ui模块的input_update处理点击事件和键盘输入
    - 调用ui模块的draw绘制
2. player
    - 歌曲开始播放时，调用对应的库播放音频
    - 提供进度跳转接口，以供ui库调用
    - 提供暂停，开始接口，以供ui库调用
    - 提供歌曲是否在播放的接口，以供ui库调用
    - 提供获取歌曲元信息结构体指针的接口，以供ui库调用
    - 提供歌曲播放进度接口，以供ui库调用
    - 提供获取歌词结构体的接口，以供ui库调用
    - 提供调节音量的接口，ui调用
    - 歌曲播放结束时，调用歌单获取出下一首歌，加载歌曲文件和歌曲元信息，并继续歌曲播放流程
3. library
    - 提供导入歌曲，歌单（文件夹）的接口，以供ui库调用（提供路径）
    - 导入时，生成结构体以及本地文件，保存歌曲地址，播放次数，调用analyzer模块分析歌曲特征
    - 提供接口返回歌曲数组指针，以供playlist调用
    - 提供增加歌曲计数器的接口 player在歌曲播放到95%时计数
    - 提供创建播放集，添加歌曲到播放集接口，获取播放集数组
    - 需设计播放集结构体和歌曲与播放集之间的相互指针
4. analyzer
    - 提供分析歌曲特征接口，library调用
    - 排序歌单，playlist调用
    - 提供快速傅里叶变换接口，ui库调用
5. playlist
    - 返回歌曲信息数组和大小，ui库调用
    - 获取下一首歌的信息
    - 获取当前播放歌的编号
6. ui
    - 根据用户操作调用相关模块
## 四.技术规范
1. player
```c
// 使用library.h 中的Song
// 定义player需要的全局变量，不需要暴露给别的模块，在源文件中定义，而非头文件
// 暂未确定类型的用type占位
static type varialbes // such as : playingSong playingProgress

void start_play();
void stop_play();
void skip_play(type to_progress);
void player_update(int delta_time); // 判断歌曲是否结束,更新歌曲进度
Song* get_music_info();
type get_music_progress();
```
2. library
```c
typedef struct{
    int id;             
    char title[128];            // 歌名
    char artist[128];           // 作者 
    char path[512];             // 文件路径
    time music_length;          // 歌曲时长
    int player_count;            // 播放次数
    float feature_vector[16]    // 特征向量（16维）
} Song;

typedef struct{
    Song *songs;
    size_t size;
    size_t capacity;
} MusicLibrary;
// 使用函数统一管理插入删除，实现动态数组

void insert(MusicLibrary* arr, Song* item);
void delete(MusicLibrary* arr, int index);

// 定义所需的全局变量 在源文件中定义，而非头文件
static type varialbes // such as : musicLibrary 
void import_music(const char * pa);
// read_only
const Song* get_library(size_t *size); // 返回song数组，约定只读,在size指针写入大小
const Song* get_song_by_id(int id);    // 通过id搜歌

```
3. analyzer
```c
void analyze_music(const char *path, float features[16]);       // 返回特征向量,存入指针中
void sort_playlist();                                           // 智能排序歌单
void register_analyzer(AudioStream stream);                     // 注册fft分析
void stop_analyzer(AudioStream stream);                         // 停止fft分析                  
void analyzer_update();                                         // 更新傅里叶计算结果
float *get_spectrum();                                          // 获得频谱数据 (此函数不计算)
```
4. ui
```c
// 略 反正没模块需要调用ui :)
```