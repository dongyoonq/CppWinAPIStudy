#include "Core.h"
#include "Scene/SceneManager.h"
#include "Core/Timer.h"
#include "Core/PathManager.h"
#include "Resource/ResourceManager.h"
#include "Resource/Texture.h"
#include "Core/Camera.h"
#include "Core/Input.h"

DEFINITION_SINGLE(CCore);
bool CCore::m_bLoop = true;

CCore::CCore() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(226);
}

CCore::~CCore() {
    DESTROY_SINGLE(CSceneManager);
    DESTROY_SINGLE(CResourceManager);
    DESTROY_SINGLE(CPathManager);
    DESTROY_SINGLE(CInput);
    DESTROY_SINGLE(CTimer);
    DESTROY_SINGLE(CCamera);
    
    ReleaseDC(m_hWnd, m_hDC);
}


bool CCore::Init(HINSTANCE hInst) {
    m_hInst = hInst;

    MyRegisterClass();
    // 해상도 설정
    m_tRS.iW = 1280;
    m_tRS.iH = 720;

    Create();

    // 화면 DC를 만들어준다.
    m_hDC = GetDC(m_hWnd);

    // 타이머 초기화
    if (!GET_SINGLE(CTimer)->Init())
        return false;

    // 경로관리자 초기화
    if (!GET_SINGLE(CPathManager)->Init())
        return false;

    // 입력관리자 초기화
    if (!GET_SINGLE(CInput)->Init(m_hWnd))
        return false;

    // 리소스관리자 초기화
    if (!GET_SINGLE(CResourceManager)->Init(hInst, m_hDC))
        return false;

    // 장면관리자 초기화
    if (!GET_SINGLE(CSceneManager)->Init())
        return false;

    // 카메라 관리자 초기화
    if (!GET_SINGLE(CCamera)->Init(POSITION(0.f, 0.f),
        m_tRS, RESOLUTION(1500, 1200)))
        return false;

    return true;
}


int CCore::Run()
{
    MSG msg;

    // 기본 메시지 루프입니다:
    while (m_bLoop)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else Logic();
    }

    return (int)msg.wParam;
}

void CCore::Logic()
{
    // 타이머 갱신
    GET_SINGLE(CTimer)->Update();
    float fDeltaTime = GET_SINGLE(CTimer)->GetDeltaTime();

    Input(fDeltaTime);
    Update(fDeltaTime);
    LateUpdate(fDeltaTime);
    Collision(fDeltaTime);
    Render(fDeltaTime);
}

void CCore::Input(float fDeltaTime)
{
    GET_SINGLE(CInput)->Update(fDeltaTime);

    GET_SINGLE(CSceneManager)->Input(fDeltaTime);
    GET_SINGLE(CCamera)->Input(fDeltaTime);
}

int CCore::Update(float fDeltaTime)
{
    GET_SINGLE(CSceneManager)->Update(fDeltaTime);
    GET_SINGLE(CCamera)->Update(fDeltaTime);
    return 0;
}

int CCore::LateUpdate(float fDeltaTime)
{
    GET_SINGLE(CSceneManager)->LateUpdate(fDeltaTime);
    return 0;
}

void CCore::Collision(float fDeltaTime)
{
    GET_SINGLE(CSceneManager)->Collision(fDeltaTime);
}

void CCore::Render(float fDeltaTime)
{
    CTexture* pBackBuffer = GET_SINGLE(CResourceManager)->GetBackBuffer();
    
    Rectangle(pBackBuffer->GetDC(), 0, 0, m_tRS.iW, m_tRS.iH);
    GET_SINGLE(CSceneManager)->Render(pBackBuffer->GetDC(), fDeltaTime);

    BitBlt(m_hDC, 0, 0, m_tRS.iW, m_tRS.iH, pBackBuffer->GetDC(), 0, 0, SRCCOPY);

    SAFE_RELEASE(pBackBuffer);
}

ATOM CCore::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = CCore::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInst;
    wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"AR13API";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));
    
    return RegisterClassExW(&wcex);
}

BOOL CCore::Create()
{

    m_hWnd = CreateWindowW(L"AR13API", L"AR13API", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

    if (!m_hWnd)
    {
        return FALSE;
    }

    RECT rc = { 0, 0, m_tRS.iW, m_tRS.iH };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top,
        SWP_NOMOVE | SWP_NOZORDER);
    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);

    return TRUE;
}

LRESULT CCore::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        m_bLoop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
