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
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
    HFONT hOldFont = (HFONT)SelectObject(hDCFrameBuffer, hFont);

    int x = FRAMEBUFFER_WIDTH / 2 - 80;
    int y = FRAMEBUFFER_HEIGHT / 2 - 100;

    TextOut(hDCFrameBuffer, x, y + 0, _T("Tutorial"), lstrlen(_T("Tutorial")));
    TextOut(hDCFrameBuffer, x, y + 50, _T("Level-1"), lstrlen(_T("Level-1")));
    TextOut(hDCFrameBuffer, x, y + 100, _T("Level-2"), lstrlen(_T("Level-2")));
    TextOut(hDCFrameBuffer, x, y + 150, _T("Start"), lstrlen(_T("Start")));   // ← 이 좌표와
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

