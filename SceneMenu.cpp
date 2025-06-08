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
    // �޴��� �ؽ�Ʈ�� ���
}

void CSceneMenu::Animate(float fElapsedTime)
{
    // �޴��� �����̹Ƿ� �ִϸ��̼� ����
}

void CSceneMenu::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
    SetBkMode(hDCFrameBuffer, TRANSPARENT);
    SetTextColor(hDCFrameBuffer, RGB(0, 0, 0));

    HFONT hFont = CreateFont(32, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        HANGEUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("���� ���"));
    HFONT hOldFont = (HFONT)SelectObject(hDCFrameBuffer, hFont);

    int x = FRAMEBUFFER_WIDTH / 2 - 80;
    int y = FRAMEBUFFER_HEIGHT / 2 - 100;

    TextOut(hDCFrameBuffer, x, y + 0, _T("Tutorial"), lstrlen(_T("Tutorial")));
    TextOut(hDCFrameBuffer, x, y + 50, _T("Level-1"), lstrlen(_T("Level-1")));
    TextOut(hDCFrameBuffer, x, y + 100, _T("Level-2"), lstrlen(_T("Level-2")));
    TextOut(hDCFrameBuffer, x, y + 150, _T("Start"), lstrlen(_T("Start")));   // �� �� ��ǥ��
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

        // �ؽ�Ʈ ��ġ�� ������ ���� ���
        int textX = FRAMEBUFFER_WIDTH / 2 - 80;
        int textY = FRAMEBUFFER_HEIGHT / 2 - 100 + 150; // "Start"�� y+150�� ����

        RECT startRect = {
            textX,             // x ����
            textY,             // y ����
            textX + 160,       // x �� (�ؽ�Ʈ �� ���)
            textY + 40         // y �� (�ؽ�Ʈ ���� ���)
        };

        if (PtInRect(&startRect, POINT{ clickX, clickY }))
        {
            OutputDebugString(L"[�޴�] Start ��ư Ŭ����\n");
            m_bStartSelected = true;
        }
    }
}

