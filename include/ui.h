#ifndef _UI_H_
#define _UI_H_

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

#define FPS 60

// color
// 左导航背景
#define COLOR_SIDEBAR \
    (Color){230, 223, 220, 255}
// 中央背景
#define COLOR_MAIN \
    (Color){230, 218, 210, 255}
// 曲库背景
#define COLOR_PANEL \
    (Color){243, 236, 230, 255}
// 底栏
#define COLOR_BAR \
    (Color){245, 239, 233, 255}
// 主要文字
#define COLOR_TEXT \
    (Color){48, 59, 73, 255}
// 次级文字
#define COLOR_TEXT_MUTED \
    (Color){148, 146, 145, 255}
// 分割线
#define COLOR_DIVIDER \
    (Color){222, 213, 206, 255}
// 被选中的导航项
#define COLOR_SELECTED \
    (Color){167, 189, 211, 100}
// 预选中的导航项
#define COLOR_PRESELECTED \
    (Color){167, 189, 211, 45}
// 播放按钮、选中内容、进度拖动点
#define COLOR_PRIMARY \
    (Color){81, 107, 137, 255}

// 圆角设置 roundness0.0-1.0 segments 0自动计算，越大越平滑
#define ROUNDSETTING 0.0, 0

// 用到的中文字体
#define FONT_PATH \
    "assets/fonts/msyhbd.ttf"
// 生成字体的像素大小
#define FONT_PIXEL 32

// 侧边栏碰撞箱 index 为select_ui
#define SIDEBAR_ITEM_RECT(index) \
    ((Rectangle){15, 95 + (index) * 44, 150, 40})

// 界面种类枚举
typedef enum
{
    PLAYING_MUSIC,
    SONG_LIBRARY,
    PLAY_COLLECTION,
    SETTING
} UI_TYPE;

#endif