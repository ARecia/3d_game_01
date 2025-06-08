#include "stdafx.h"
#include "SceneStage1.h"
#include "SceneStage2.h"
#include "SceneMenu.h"

// SceneStage1.cpp
CSceneStage1::CSceneStage1(CPlayer* pPlayer) : CScene(pPlayer)
{
    BuildObjects();
}


CSceneStage1::~CSceneStage1()
{
}

void CSceneStage1::BuildObjects()
{
    OutputDebugString(L"[DEBUG] CSceneStage1::BuildObjects 시작됨\n");

    m_pAirplane = new CAirplanePlayer();
    m_pAirplane->SetPosition(0.0f, 0.0f, 0.0f);

    if (m_pPlayer && m_pPlayer->GetCamera())
    {
        m_pAirplane->SetCamera(m_pPlayer->GetCamera());
    }
    else
    {
        OutputDebugString(L"[ERROR] m_pPlayer 또는 GetCamera()가 null입니다!\n");
    }

    m_nObjects = 1;
    m_ppObjects = new CGameObject * [m_nObjects];
    m_ppObjects[0] = m_pAirplane;

    OutputDebugString(L"[DEBUG] CSceneStage1::BuildObjects 완료됨\n");
}



void CSceneStage1::Animate(float fElapsedTime)
{
    if (m_pAirplane)
    {
        m_pAirplane->Move(0.0f, 0.0f, 20.0f * fElapsedTime);  // 직진
        m_pAirplane->Animate(fElapsedTime);

        // 도착 조건
        if (m_pAirplane->GetPosition().z >= 500.0f)
        {
            m_bFinished = true;
        }
    }

    CScene::Animate(fElapsedTime);
}

void CSceneStage1::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
    SetBkMode(hDCFrameBuffer, TRANSPARENT);
    SetTextColor(hDCFrameBuffer, RGB(0, 0, 255));

    TextOut(hDCFrameBuffer, 10, 10, _T("Press N: Next Level | ESC: Menu"), 34);

    CScene::Render(hDCFrameBuffer, pCamera);
}

void CSceneStage1::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
    if (nMessageID == WM_KEYDOWN)
    {
        if (wParam == 'N') m_bFinished = true;
        else if (wParam == VK_ESCAPE) m_bBackToMenu = true;
    }
}
