#include <windows.h>
// 窗口过程函数
LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildWindProc(HWND, UINT, WPARAM, LPARAM);

WNDPROC Button1Proc;

int WINAPI WinMain(
    HINSTANCE hInstance,         // handle to current instance
    HINSTANCE hPrevInstance,     // handle to previous instance
    LPSTR lpCmdLine,             // command line
    int nCmdShow                 // show state
)
{
    // 窗口类
    WNDCLASS wndclass;
    wndclass.cbClsExtra = 0;                                          // 类附加内存
    wndclass.cbWndExtra = 0;                                          // 窗口附加内存
    wndclass.hbrBackground = (HBRUSH) GetStockObject(COLOR_WINDOW);    // 背景画刷句柄
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);                   // 窗口光标句柄
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);                       // 窗口图标句柄
    wndclass.hInstance = hInstance;                                   // 包含窗口过程函数的程序实例
    wndclass.lpfnWndProc = WinProc;                                // 只想窗口过程函数的指针
    wndclass.lpszClassName = "CRoot";                                // 窗口类名称
    wndclass.lpszMenuName = NULL;                                     // 菜单资源
    wndclass.style = CS_HREDRAW | CS_VREDRAW;                         // 窗口样式
    RegisterClass(&wndclass);
    // 创建窗口， 定义一个变量用来保存成功创建窗口后返回的句柄
    HWND hwnd;
    hwnd = CreateWindow("CRoot","Hello World",WS_CAPTION|WS_SYSMENU,
                        500, 240, 200, 120,
                        NULL,NULL,hInstance,NULL
                       );
    // 显示及刷新窗口
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);
    // 定义消息结构体
    MSG msg;
    while (GetMessage(&msg,NULL,0,0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
// 窗口过程函数
LRESULT CALLBACK WinProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
    WORD wmId    = LOWORD(wParam);
    switch(uMsg) {
    case WM_CREATE: {
        HWND hBtn1=CreateWindow("Button","按钮1",WS_VISIBLE|WS_CHILD,
                                50,20,70,40,hwnd,(HMENU)0,((LPCREATESTRUCT)lParam)->hInstance,0);
        Button1Proc= (WNDPROC)SetWindowLong(hBtn1, GWL_WNDPROC,(LONG)ChildWindProc);
    }
    break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
LRESULT CALLBACK ChildWindProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC				hdc;
    PAINTSTRUCT		ps;
    RECT			rect;
    switch (message) {
    case WM_CREATE:
        SetWindowLong(hwnd, 0, 0);
        return 0;
    case WM_LBUTTONDOWN:
        MessageBoxA(NULL,"Hello Button2!","My TestProject",MB_OK);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return CallWindowProc(Button1Proc,hwnd, message, wParam, lParam);
}