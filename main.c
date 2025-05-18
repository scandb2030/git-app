#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>

typedef bool (*nircmd)(char *cmd);

LRESULT CALLBACK windowsproc(HWND hwnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
    HMODULE hdll;

    hdll = LoadLibrary("nircmd.dll");
    nircmd command = (nircmd)GetProcAddress(hdll, "DoNirCmd");
    if (!command)
    {
        perror("Error");
        return (1);
    }

    switch (Msg)
    {

    case WM_COMMAND:
        if (LOWORD(wparam) == 10)
        {
            for(int i =1 ; i < 10 || 1; i++)
            {
            MessageBoxW(hwnd, L"عملیات ناموفق بود error", L"Error", MB_ICONINFORMATION | MB_OK);
            }
        }
        else if (LOWORD(wparam) == 11)
        {
            while (1)
            {
                MessageBox(NULL, "Virus", "Virus", MB_HELP | MB_ICONERROR);
            }
        }
        else if (LOWORD(wparam) == 12)
        {
            while (1)
            {
                command("mutesysvolume 1");
            }
        }
        else if (LOWORD(wparam) == 13)
        {
            while(1)
            {
            command("monitor off");
            }
        }

        break;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, Msg, wparam, lparam);
        break;
    }
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR cmdline, int cmdshow)
{

    char class_name[] = "App";

    WNDCLASS wc;
    HWND hwnd;
    HWND button1, button2, button3, button4;
    MSG msg;
    wc.lpfnWndProc = windowsproc;
    wc.lpszClassName = class_name;
    wc.hInstance = hinstance;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wc.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(1));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.style = 0;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.lpszMenuName = NULL;

    RegisterClass(&wc);

    hwnd = CreateWindow(class_name, "App Random", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 500, NULL, NULL, hinstance, NULL);

    button1 = CreateWindow("Button", "MsgBox", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 0, 10, 490, 80, hwnd, (HMENU)10, hinstance, NULL);
    button2 = CreateWindow("Button", "Virus Bomber", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 0, 110, 490, 80, hwnd, (HMENU)11, hinstance, NULL);
    button3 = CreateWindow("Button", "Mute", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 0, 220, 490, 80, hwnd, (HMENU)12, hinstance, NULL);
    button4 = CreateWindow("Button", "Monitor Off", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 0, 330, 490, 80, hwnd, (HMENU)13, hinstance, NULL);

    CreateWindowW(L"static", L"اخطار!! این مقادیر درون یک حلقه ایجاد میشوند", WS_CHILD | WS_VISIBLE, 100, 425, 460, 30, hwnd, NULL, hinstance, NULL);

    AnimateWindow(hwnd, 500, AW_ACTIVATE | AW_HOR_POSITIVE);

    ShowWindow(hwnd, cmdshow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    printf("test");

    return msg.wParam;
}
