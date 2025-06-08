#include "stdafx.h"
#include "SceneMenu.h"

CSceneMenu::CSceneMenu(CPlayer* pPlayer) : CScene(pPlayer)
{
    BuildObjects();
}

CSceneMenu::~CSceneMenu()
{
}

void CSceneMenu::BuildObjects()
{
    // Prepare clickable rectangles for each menu item
    int x = FRAMEBUFFER_WIDTH / 2 - 80;
    int y = FRAMEBUFFER_HEIGHT / 2 - 100;

    for (int i = 0; i < MENU_COUNT; ++i)
    {
        m_rcMenuItems[i].left   = x;
        m_rcMenuItems[i].top    = y + i * 50;
        m_rcMenuItems[i].right  = x + 160;
        m_rcMenuItems[i].bottom = y + i * 50 + 40;
    }
}

void CSceneMenu::Animate(float fElapsedTime)
{
    // No animation required for the menu scene
}

void CSceneMenu::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
    SetBkMode(hDCFrameBuffer, TRANSPARENT);
    SetTextColor(hDCFrameBuffer, RGB(0, 0, 0));

    HFONT hFont = CreateFont(32, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        HANGEUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T(""));
    HFONT hOldFont = (HFONT)SelectObject(hDCFrameBuffer, hFont);

    int x = FRAMEBUFFER_WIDTH / 2 - 80;
    int y = FRAMEBUFFER_HEIGHT / 2 - 100;

    TextOut(hDCFrameBuffer, x, y + 0, _T("Tutorial"), lstrlen(_T("Tutorial")));
    TextOut(hDCFrameBuffer, x, y + 50, _T("Level-1"), lstrlen(_T("Level-1")));
    TextOut(hDCFrameBuffer, x, y + 100, _T("Level-2"), lstrlen(_T("Level-2")));
    TextOut(hDCFrameBuffer, x, y + 150, _T("Start"), lstrlen(_T("Start")));
    TextOut(hDCFrameBuffer, x, y + 200, _T("End"), lstrlen(_T("End")));

    SelectObject(hDCFrameBuffer, hOldFont);
    DeleteObject(hFont);
}

void CSceneMenu::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
    if (nMessageID == WM_LBUTTONDOWN)
    {
        int clickX = LOWORD(lParam);
        int clickY = HIWORD(lParam);
        POINT pt{ clickX, clickY };

        for (int i = 0; i < MENU_COUNT; ++i)
        {
            if (PtInRect(&m_rcMenuItems[i], pt))
            {
                switch (i)
                {
                case MENU_TUTORIAL:
                    OutputDebugString(L"[Menu] Tutorial selected\n");
                    m_nCurrentSelection = MENU_TUTORIAL;
                    break;
                case MENU_LEVEL1:
                    OutputDebugString(L"[Menu] Level-1 selected\n");
                    m_nCurrentSelection = MENU_LEVEL1;
                    break;
                case MENU_LEVEL2:
                    OutputDebugString(L"[Menu] Level-2 selected\n");
                    m_nCurrentSelection = MENU_LEVEL2;
                    break;
                case MENU_START:
                    OutputDebugString(L"[Menu] Start clicked\n");
                    m_bStartSelected = true;
                    break;
                case MENU_END:
                    OutputDebugString(L"[Menu] End clicked\n");
                    PostQuitMessage(0);
                    break;
                }
                break;
            }
        }
    }
}
