#include <raylib.h>
#include <time.h>
#include <stdlib.h>
#include "ui.h"

// 绘制从（a,b）宽高为（c,d）的圆角矩阵 c>a d>b
#define DRAW_RECT(a, b, c, d, color) \
    DrawRectangleRounded((Rectangle){(a), (b), (c), (d)}, ROUNDSETTING, color)

// 定义变量
// 中文字体
static Font chinese_font;

static UI_TYPE selected_ui = SONG_LIBRARY;
static UI_TYPE preselected_ui = -1;

// 定义函数
// 加载中文常用字体
static void LoadChinese()
{
    int count = 0;
    const int capabity = 95 + 20992 + 64 + 240;
    int *codepoints = malloc(sizeof(int) * capabity);
    int i;
    // 英文字母，数字，半角标点
    for (i = 0x20; i <= 0x7E; i++)
        codepoints[count++] = i;
    // 汉字
    for (i = 0x4E00; i <= 0x9FFF; i++)
        codepoints[count++] = i;
    // 加载字体
    chinese_font = LoadFontEx(FONT_PATH, FONT_PIXEL, codepoints, count);
    free(codepoints);
}

/*
 * @brief 渲染中文
 * @param text 渲染的文字
 * @param x,y 渲染的坐标
 * @param fontSize 字体大小
 * @param tint 颜色
 */
static inline void DrawChinese(const char *text, float x, float y, float fontSize, Color tint)
{
    DrawTextEx(chinese_font, text, (Vector2){x, y}, fontSize, 1.0f, tint);
}

// 绘制主界面ui(通用)
static void DrawMainUi()
{
    // 左侧导航
    DrawRectangle(0, 0, 180, 640, COLOR_SIDEBAR);
    // 底部播放控制栏
    DrawRectangle(0, 640, 1080, 80, COLOR_BAR);
    // 分割线
    DrawLine(0, 640, 1080, 640, COLOR_DIVIDER);
    DrawLine(180, 0, 180, 640, COLOR_DIVIDER);
    // 左侧导航文字
    DrawChinese("正在播放", 57, 107, 18, COLOR_TEXT);
    DrawChinese("音乐库", 57, 151, 18, COLOR_TEXT);
    DrawChinese("播放集", 57, 195, 18, COLOR_TEXT);
    DrawChinese("设置", 57, 239, 16, COLOR_TEXT);
    // 绘制被选中项强调框
    DrawRectangleRounded(SIDEBAR_ITEM_RECT(selected_ui), 0.50f, 30, COLOR_SELECTED);
    // 绘制被预选中项强调框
    if (preselected_ui != -1)
        DrawRectangleRounded(SIDEBAR_ITEM_RECT(preselected_ui), 0.50f, 30, COLOR_PRESELECTED);
}

static void DrawPlayingMusic()
{

    // 中央播放区域
    DRAW_RECT(180, 0, 520, 640, COLOR_MAIN);
    // 右侧曲库
    DRAW_RECT(700, 0, 380, 640, COLOR_PANEL);

    // 分割线
    DrawLine(700, 0, 700, 640, COLOR_DIVIDER);
    DrawLine(26, 374, 154, 374, COLOR_DIVIDER);

    // 临时占位
    {
        DrawText("Sunset Drive", 440 - MeasureText("Sunset Drive", 30) / 2,
                 463, 30, COLOR_TEXT);
        DrawText("All Songs", 725, 97, 14, COLOR_TEXT);
        DrawText("Sunset Drive", 82, 660, 16, COLOR_TEXT);

        // 次级文字
        DrawText("NOW PLAYING", 440 - MeasureText("NOW PLAYING", 12) / 2,
                 42, 12, COLOR_TEXT_MUTED);
        DrawText("lofi house - Chill Vibes",
                 440 - MeasureText("lofi house - Chill Vibes", 14) / 2,
                 507, 14, COLOR_TEXT_MUTED);
        DrawText("The evening breeze reminds me",
                 440 - MeasureText("The evening breeze reminds me", 14) / 2,
                 550, 14, COLOR_TEXT);
        DrawText("of those quiet days.",
                 440 - MeasureText("of those quiet days.", 14) / 2,
                 575, 14, COLOR_TEXT_MUTED);
        DrawText("Artists", 818, 97, 14, COLOR_TEXT_MUTED);
        DrawText("Albums", 891, 97, 14, COLOR_TEXT_MUTED);
        DrawText("Folders", 964, 97, 14, COLOR_TEXT_MUTED);
        DrawText("Library / 128 songs", 724, 151, 12, COLOR_TEXT_MUTED);
        DrawText("lofi house", 82, 682, 12, COLOR_TEXT_MUTED);
        DrawText("01:24", 451, 675, 12, COLOR_TEXT_MUTED);
        DrawText("03:42", 761, 675, 12, COLOR_TEXT_MUTED);
    }
}

static void DrawSongLibrary()
{
    DrawChinese("音乐库占位符", 480, 300, 18, COLOR_TEXT);
}

static void DrawPlayCollection()
{
    DrawChinese("播放集占位符", 480, 300, 18, COLOR_TEXT);
}

static void DrawSetting()
{
    DrawChinese("设置占位符", 480, 300, 18, COLOR_TEXT);
}

static void handle_user_input()
{
    preselected_ui = -1;
    Vector2 mouse = GetMousePosition();
    for (size_t i = 0; i < 4; i++)
    {
        if (CheckCollisionPointRec(mouse, SIDEBAR_ITEM_RECT(i)))
        {
            if (i != selected_ui)
            {
                preselected_ui = i;
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                selected_ui = i;
            }
        }
    }
}

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test"); // 初始化窗口
    LoadChinese();                                   // 初始化字体
    SetTraceLogLevel(LOG_WARNING);                   // 设置日志提示等级
    SetTargetFPS(FPS);                               // 设置fps
    while (!WindowShouldClose())
    {

        handle_user_input(); // 处理用户输入

        // 开始绘制
        BeginDrawing();
        ClearBackground(COLOR_MAIN);

        DrawMainUi(); // 绘制通用界面
        // for (size_t i = 0; i < 4; i++)
        // {
        //     DrawRectangleRounded(SIDEBAR_ITEM_RECT(i), ROUNDSETTING, RED);
        // }
        // 绘制不同分页
        switch (selected_ui)
        {
        case PLAYING_MUSIC:
            DrawPlayingMusic();
            break;
        case SONG_LIBRARY:
            DrawSongLibrary();
            break;
        case PLAY_COLLECTION:
            DrawPlayCollection();
            break;
        case SETTING:
            DrawSetting();
            break;
        default:
            break;
        }

        EndDrawing();
    }
    CloseWindow();
}