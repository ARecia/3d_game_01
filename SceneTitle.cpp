#include "stdafx.h"
#include "SceneTitle.h"
#include <string>

CSceneTitle::CSceneTitle(CPlayer* pPlayer) : CScene(pPlayer)
{
    BuildObjects();
}

CSceneTitle::~CSceneTitle()
{
    if (m_pExplosive) delete m_pExplosive;
}

void CSceneTitle::BuildObjects()
{
    // 텍스트만 렌더링하는 씬이므로 별도 오브젝트 필요 없음
}

void CSceneTitle::Animate(float fElapsedTime)
{
    m_fRotationAngle += 90.0f * fElapsedTime;

    if (m_bExploded)
    {
        m_fExplosionTime += fElapsedTime;

        if (m_pExplosive)
            m_pExplosive->Animate(fElapsedTime);

        if (m_fExplosionTime > 1.0f)
        {
            m_bSceneFinished = true;
        }
    }
}


void CSceneTitle::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
    SetBkMode(hDCFrameBuffer, TRANSPARENT);
    SetTextColor(hDCFrameBuffer, RGB(255, 255, 0));

    HFONT hFont = CreateFont(36, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        HANGEUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
    HFONT hOldFont = (HFONT)SelectObject(hDCFrameBuffer, hFont);

    // 회전 연출용 위치 보간
    int xMid = FRAMEBUFFER_WIDTH / 2;
    int yMid = FRAMEBUFFER_HEIGHT / 2;
    int offset = (int)(20 * sinf(XMConvertToRadians(m_fRotationAngle)));

    TextOut(hDCFrameBuffer, xMid - 120, yMid - 80 + offset,
        _T("3D 게임 프로그래밍"), lstrlen(_T("3D 게임 프로그래밍")));

    // 폭발이 아직 안 된 경우만 "김윤구" 출력
    if (!m_bExploded)
    {
        TextOut(hDCFrameBuffer, xMid - 60, yMid + 40 - offset,
            _T("김윤구"), lstrlen(_T("김윤구")));
    }

    // 폭발 오브젝트가 존재하면 렌더링
    if (m_pExplosive)
    {
        m_pExplosive->Render(hDCFrameBuffer, pCamera); // ✅ 3D 렌더링 호출
    }

    SelectObject(hDCFrameBuffer, hOldFont);
    DeleteObject(hFont);
}


void CSceneTitle::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
    if (m_bExploded) return;

    if (nMessageID == WM_LBUTTONDOWN)
    {
        int mouseX = LOWORD(lParam);
        int mouseY = HIWORD(lParam);

        RECT nameRect = { FRAMEBUFFER_WIDTH / 2 - 60, FRAMEBUFFER_HEIGHT / 2 + 40 - 20,
                          FRAMEBUFFER_WIDTH / 2 + 60, FRAMEBUFFER_HEIGHT / 2 + 40 + 20 };

        if (PtInRect(&nameRect, POINT{ mouseX, mouseY }))
        {
            m_bExploded = true;
            m_fExplosionTime = 0.0f;

            // 폭발 오브젝트 생성 및 설정
            m_pExplosive = new CExplosiveObject();

            // 폭발 위치를 화면 기준 중심 또는 클릭 좌표로 설정 (원하는 위치 조정 가능)
            float fx = (float)(FRAMEBUFFER_WIDTH / 2);
            float fy = (float)(FRAMEBUFFER_HEIGHT / 2 + 40);
            m_pExplosive->SetPosition(fx, fy, 0.0f);
        }
    }
}

