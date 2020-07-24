


#include "framework.h"
#include "astrStudy.h"
#include <list>

using namespace std;

#define MAX_LOADSTRING 100

enum MOVE_DIR
{
    MD_BACK = -1,
    MD_None,
    MD_FRONT
};

typedef struct _tagRectangle
{
    float  l, t, r, b;
}RECTANGLE, * PRECTANGLE;

typedef struct _tagMonster
{
    RECTANGLE tRC;
    float     fSpeed;
    float     fTime;
    float     fLimitTime;
    int       iDir;    
}MONSTER, *PMONSTER;


HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];            
HWND   g_hWnd;
HDC    g_hDC;
bool   g_bLoop = true;
RECTANGLE   g_tPlayerRC = { 100, 100, 200, 200 };
MONSTER    g_tMonster;

typedef struct _tagBullet
{
    RECTANGLE   rc;
    float       fDist;
    float       fLimitDist;
}BULLET, *PBULLET;


list<BULLET> g_PlayerBulletList;


list<BULLET> g_MonsterBulletList;



LARGE_INTEGER   g_tSecond;
LARGE_INTEGER   g_tTime;
float           g_fDeltaTime;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void Run();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    

    
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ASTRSTUDY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

  
    g_hDC = GetDC(g_hWnd);

  
    g_tMonster.tRC.l = 800.f - 100.f;
    g_tMonster.tRC.t = 0.f;
    g_tMonster.tRC.r = 800.f;
    g_tMonster.tRC.b = 100.f;
    g_tMonster.fSpeed = 300.f;
    g_tMonster.fTime = 0.f;
    g_tMonster.fLimitTime = 1.3f;
    g_tMonster.iDir = MD_FRONT;


    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASTRSTUDY));

    MSG msg;

    QueryPerformanceFrequency(&g_tSecond);
    QueryPerformanceCounter(&g_tTime);


    
    while (g_bLoop)
    {
       
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

       
        else
        {
            static int iCount;
            ++iCount;

            Run();

        }
    }

    ReleaseDC(g_hWnd, g_hDC);

    return (int)msg.wParam;
}




ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASTRSTUDY));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_astrStudy);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    g_hWnd = hWnd;

    
    RECT rc = { 0, 0, 1280, 720 };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    
    SetWindowPos(hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left,
        rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);
    

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        
        EndPaint(hWnd, &ps);
    }
    break;
    
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void Run()
{
   
    LARGE_INTEGER  tTime;
    QueryPerformanceCounter(&tTime);

    g_fDeltaTime = (tTime.QuadPart - g_tTime.QuadPart) /
        (float)g_tSecond.QuadPart;

    g_tTime = tTime;

    static float fTimeScale = 1.f;

    if (GetAsyncKeyState(VK_F1) & 0x8000)
    {
        fTimeScale -= g_fDeltaTime;

        if (fTimeScale < 0.f)
            fTimeScale = 0.f;
    }

    if (GetAsyncKeyState(VK_F2) & 0x8000)
    {
        fTimeScale += g_fDeltaTime;

        if (fTimeScale > 1.f)
            fTimeScale = 1.f;
    }

    
    float  fSpeed = 400.f * g_fDeltaTime * fTimeScale;



    if (GetAsyncKeyState('D') & 0x8000)
    {
        g_tPlayerRC.l += fSpeed;
        g_tPlayerRC.r += fSpeed;

    }

    if (GetAsyncKeyState('A') & 0x8000)
    {
        g_tPlayerRC.l -= fSpeed;
        g_tPlayerRC.r -= fSpeed;

    }

    if (GetAsyncKeyState('W') & 0x8000)
    {
        g_tPlayerRC.t -= fSpeed;
        g_tPlayerRC.b -= fSpeed;

    }

    if (GetAsyncKeyState('S') & 0x8000)
    {
        g_tPlayerRC.t += fSpeed;
        g_tPlayerRC.b += fSpeed;
    }

    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        BULLET  tBullet;

        tBullet.rc.l = g_tPlayerRC.r;
        tBullet.rc.r = g_tPlayerRC.r + 50.f;
        tBullet.rc.t = (g_tPlayerRC.t + g_tPlayerRC.b) / 2.f - 25.f;
        tBullet.rc.b = tBullet.rc.t + 75.f;
        tBullet.fDist = 0.f;
        tBullet.fLimitDist = 500.f;


        g_PlayerBulletList.push_back(tBullet);
        
    }
    
    RECT   rcWindow;
    GetClientRect(g_hWnd, &rcWindow);
    SetRect(&rcWindow, 0, 0, 800, 600);

    if (g_tPlayerRC.l < 0)
    {
        g_tPlayerRC.l = 0;
        g_tPlayerRC.r = 100;
    }

    else if (g_tPlayerRC.r > rcWindow.right)
    {
        g_tPlayerRC.l = rcWindow.right - 100;
        g_tPlayerRC.r = rcWindow.right;
    }

    if (g_tPlayerRC.t < 0)
    {
        g_tPlayerRC.t = 0;
        g_tPlayerRC.b = 100;
    }

    else if (g_tPlayerRC.b > rcWindow.bottom)
    {
        g_tPlayerRC.b = rcWindow.bottom;
        g_tPlayerRC.t = rcWindow.bottom - 100;

    }



    g_tMonster.tRC.t += g_tMonster.fSpeed * g_fDeltaTime * fTimeScale * g_tMonster.iDir;
    g_tMonster.tRC.b += g_tMonster.fSpeed * g_fDeltaTime * fTimeScale * g_tMonster.iDir;

    if (g_tMonster.tRC.b >= 600)
    {
        g_tMonster.iDir = MD_BACK;
        g_tMonster.tRC.b = 600;
        g_tMonster.tRC.t = 500;
    }

    else if (g_tMonster.tRC.t <= 0)
    {
        g_tMonster.iDir =  MD_FRONT;
        g_tMonster.tRC.b = 100;
        g_tMonster.tRC.t = 0;

        
        g_tMonster.fTime += g_fDeltaTime * fTimeScale;

        if (g_tMonster.fTime >= g_tMonster.fLimitTime)
        {
            g_tMonster.fTime -= g_tMonster.fLimitTime;
            

            BULLET  tBullet = {};

            tBullet.rc.r = g_tMonster.tRC.l;
            tBullet.rc.l = g_tMonster.tRC.l - 50.f;
            tBullet.rc.t = (g_tMonster.tRC.t + g_tMonster.tRC.b) / 2.f - 25.f;
            tBullet.rc.b = tBullet.rc.t + 50.f;
            tBullet.fDist = 0.f;
            tBullet.fLimitDist = 800.f;


            g_MonsterBulletList.push_back(tBullet);
        }
        
    }

    
    list<BULLET>::iterator    iter;
    list<BULLET>::iterator    iterEnd = g_PlayerBulletList.end();

    fSpeed = 600.f * g_fDeltaTime * fTimeScale;
    
    for (iter = g_PlayerBulletList.begin(); iter != iterEnd;)
    {
        (*iter).rc.l += fSpeed;
        (*iter).rc.r += fSpeed;

        (*iter).fDist += fSpeed;

        if ((*iter).fDist >= (*iter).fLimitDist)
        {
            iter = g_PlayerBulletList.erase(iter);
            iterEnd = g_PlayerBulletList.end();
        }

        else if (800 <= (*iter).rc.l)
        {
            iter = g_PlayerBulletList.erase(iter);
            iterEnd = g_PlayerBulletList.end();
        }

        else
            ++iter;
        
    }

    
    iterEnd = g_MonsterBulletList.end();
    for (iter = g_MonsterBulletList.begin(); iter != iterEnd;)
    {
        (*iter).rc.l -= fSpeed;
        (*iter).rc.r -= fSpeed;

        (*iter).fDist += fSpeed;

        if ((*iter).fDist >= (*iter).fLimitDist)
        {
            iter = g_MonsterBulletList.erase(iter);
            iterEnd = g_MonsterBulletList.end();
        }

        else if (0 >= (*iter).rc.r)
        {
            iter = g_MonsterBulletList.erase(iter);
            iterEnd = g_MonsterBulletList.end();
        }

        else if (g_tPlayerRC.l <= (*iter).rc.r && (*iter).rc.l <= g_tPlayerRC.r &&
            g_tPlayerRC.t <= (*iter).rc.b && (*iter).rc.t <= g_tPlayerRC.b)
        {
            iter = g_MonsterBulletList.erase(iter);
            iterEnd = g_MonsterBulletList.end();
        }

        else
           ++iter;
       
    }

   

    Rectangle(g_hDC, g_tMonster.tRC .l, g_tMonster.tRC.t, g_tMonster.tRC.r, g_tMonster.tRC.b);
    Rectangle(g_hDC, g_tPlayerRC.l, g_tPlayerRC.t, g_tPlayerRC.r, g_tPlayerRC.b);

    iterEnd = g_PlayerBulletList.end();
    for (iter = g_PlayerBulletList.begin(); iter != iterEnd; ++iter)
    {
        Rectangle(g_hDC, (*iter).rc.l, (*iter).rc.t, (*iter).rc.r, (*iter).rc.b);
    }

    
    iterEnd = g_MonsterBulletList.end();
    for (iter = g_MonsterBulletList.begin(); iter != iterEnd; ++iter)
    {
        Rectangle(g_hDC, (*iter).rc.l, (*iter).rc.t, (*iter).rc.r, (*iter).rc.b);
    }
    
    
}
