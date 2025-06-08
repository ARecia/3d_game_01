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
    // 메뉴는 텍스트만 출력
}

void CSceneMenu::Animate(float fElapsedTime)
{
    // 메뉴는 정적이므로 애니메이션 없음
}

void CSceneMenu::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
    SetBkMode(hDCFrameBuffer, TRANSPARENT);
    SetTextColor(hDCFrameBuffer, RGB(0, 0, 0));

    HFONT hFont = CreateFont(32, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        HANGEUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        int baseY = FRAMEBUFFER_HEIGHT / 2 - 100;

        RECT tutorialRect = { textX, baseY + 0,   textX + 160, baseY + 40 };
        RECT level1Rect  = { textX, baseY + 50,  textX + 160, baseY + 90 };
        RECT level2Rect  = { textX, baseY + 100, textX + 160, baseY + 140 };
        RECT startRect   = { textX, baseY + 150, textX + 160, baseY + 190 };
        RECT endRect     = { textX, baseY + 200, textX + 160, baseY + 240 };
        POINT pt{ clickX, clickY };

        if (PtInRect(&tutorialRect, pt))
        {
            OutputDebugString(L"[Menu] Tutorial click\n");
            m_bTutorialSelected = true;
        }
        else if (PtInRect(&level1Rect, pt))
        {
            OutputDebugString(L"[Menu] Level-1 click\n");
            m_bLevel1Selected = true;
        }
        else if (PtInRect(&level2Rect, pt))
            OutputDebugString(L"[Menu] Level-2 click\n");
            m_bLevel2Selected = true;
        }
        else if (PtInRect(&startRect, pt))
        {
            OutputDebugString(L"[Menu] Start click\n");
        else if (PtInRect(&endRect, pt))
        {
            OutputDebugString(L"[Menu] End click\n");
            m_bEndSelected = true;
        }

    SelectObject(hDCFrameBuffer, hOldFont);
    DeleteObject(hFont);
}


void CSceneMenu::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
    if (nMessageID == WM_LBUTTONDOWN)
    {
        int clickX = LOWORD(lParam);
        int clickY = HIWORD(lParam);

        // 텍스트 위치와 동일한 기준 사용
        int textX = FRAMEBUFFER_WIDTH / 2 - 80;
        int textY = FRAMEBUFFER_HEIGHT / 2 - 100 + 150; // "Start"가 y+150에 있음

        RECT startRect = {
            textX,             // x 시작
            textY,             // y 시작
            textX + 160,       // x 끝 (텍스트 폭 고려)
            textY + 40         // y 끝 (텍스트 높이 고려)
        };

        if (PtInRect(&startRect, POINT{ clickX, clickY }))
        {
            OutputDebugString(L"[메뉴] Start 버튼 클릭됨\n");
            m_bStartSelected = true;
        }
    }
}

